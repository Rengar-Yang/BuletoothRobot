#include "stm32f10x.h"                  // Device header

void zhongduan_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//�����жϵ�����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//EXTI����Ҫ����ȥ����ʱ�ӣ�������������������
	
	//����GPIO
	GPIO_InitTypeDef GPIO_InitStruture;
	GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruture.GPIO_Pin=GPIO_Pin_14;
	GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruture);
	
	//����AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	//�����ж�
	EXTI_InitTypeDef EXIT_InitStructure;
	EXIT_InitStructure.EXTI_Line=EXTI_Line14;//����������·
	EXIT_InitStructure.EXTI_LineCmd=ENABLE;
	EXIT_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//�ж�ģʽ
	EXIT_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش��������Ը��ĳ������ػ����������½���
	EXTI_Init(&EXIT_InitStructure);
	
	//����MVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2��ռ���ȼ���2��Ӧ���ȼ�
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;//EXTI10��15�������ͨ����
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14)==SET)//�жϾ������ĸ����������ж�
	{
		
		EXTI_ClearITPendingBit(EXTI_Line14);//����жα�־λ
	}

}




