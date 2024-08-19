#include "stm32f10x.h"                  // Device header

int16_t Encoder_count;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//�����жϵ�����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//EXTI����Ҫ����ȥ����ʱ�ӣ�������������������
	
	//����GPIO
	GPIO_InitTypeDef GPIO_InitStruture;
	GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruture.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruture);
	
	//����AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	//�����ж�
	EXTI_InitTypeDef EXIT_InitStructure;
	EXIT_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1;//����������·
	EXIT_InitStructure.EXTI_LineCmd=ENABLE;
	EXIT_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//�ж�ģʽ
	EXIT_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش��������Ը��ĳ������ػ����������½���
	EXTI_Init(&EXIT_InitStructure);
	
	//����MVIC,����������Ҫ�ֱ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2��ռ���ȼ���2��Ӧ���ȼ�
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;//EXTI10��15�������ͨ����
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);

  NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;//EXTI10��15�������ͨ����
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
	if (EXTI_GetITStatus(EXTI_Line0)==SET)//һ��ͨ����Ҳ���Բ��ж�
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
	if (EXTI_GetITStatus(EXTI_Line1)==SET)//һ��ͨ����Ҳ���Բ��ж�
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1 )==0)
		{
			Encoder_count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}

}

