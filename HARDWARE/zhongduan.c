#include "stm32f10x.h"                  // Device header

void zhongduan_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启中断的三个时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//EXTI不需要额外去开启时钟，因此软件开启两个即可
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStruture;
	GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruture.GPIO_Pin=GPIO_Pin_14;
	GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruture);
	
	//配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	//开启中断
	EXTI_InitTypeDef EXIT_InitStructure;
	EXIT_InitStructure.EXTI_Line=EXTI_Line14;//引脚所在线路
	EXIT_InitStructure.EXTI_LineCmd=ENABLE;
	EXIT_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
	EXIT_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发，可以更改成上升沿或者上升和下降沿
	EXTI_Init(&EXIT_InitStructure);
	
	//配置MVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2抢占优先级，2相应优先级
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;//EXTI10到15都在这个通道内
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14)==SET)//判断具体是哪个引脚来的中断
	{
		
		EXTI_ClearITPendingBit(EXTI_Line14);//清除中段标志位
	}

}




