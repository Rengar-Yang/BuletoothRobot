#include "stm32f10x.h"                  // Device header

int16_t Encoder_count;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启中断的三个时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//EXTI不需要额外去开启时钟，因此软件开启两个即可
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStruture;
	GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruture.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruture);
	
	//配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	//开启中断
	EXTI_InitTypeDef EXIT_InitStructure;
	EXIT_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1;//引脚所在线路
	EXIT_InitStructure.EXTI_LineCmd=ENABLE;
	EXIT_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
	EXIT_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发，可以更改成上升沿或者上升和下降沿
	EXTI_Init(&EXIT_InitStructure);
	
	//配置MVIC,两个引脚需要分别配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2抢占优先级，2相应优先级
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;//EXTI10到15都在这个通道内
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);

  NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;//EXTI10到15都在这个通道内
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);

}

int16_t Encoder_get(void)
{
		int16_t Temp;
	  Temp=Encoder_count;
		Encoder_count=0;
		return Temp;
}


void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0)==SET)//一个通道的也可以不判断
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
		{
			Encoder_count --;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}

}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1)==SET)//一个通道的也可以不判断
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1 )==0)
		{
			Encoder_count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}

}

