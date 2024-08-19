#include "stm32f10x.h"                  // Device header


void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//TIM2��APB1������
	
	TIM_InternalClockConfig(TIM2);//ѡ��ʹ���ڲ�ʱ�ӣ��ϵ�Ĭ�����������˿��Բ�д
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//ʱ����Ԫ��������
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//һ��Ƶ�����ǲ���Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=10000-1;//�Զ���װ����ֵARR��72M/(ARR+1)/(PSC+1)
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;//Ԥ��Ƶ����ֵPSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//�ظ���������ֵ���߼���ʱ��������
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��ʱ����Ԫ,�ᴥ��һ���¼����ж�

	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//����ʹ���ж�

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ѡ������
	
	//�ж�����
	NVIC_InitTypeDef NVIC_InitStrcture;
	
	NVIC_InitStrcture.NVIC_IRQChannel=TIM2_IRQn;//TIM2���ж�ͨ��
	NVIC_InitStrcture.NVIC_IRQChannelCmd=ENABLE;//
	NVIC_InitStrcture.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStrcture.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStrcture);
	
	TIM_Cmd(TIM2,ENABLE);//������ʱ��
}

//void TIM2_IRQHandler(void)//�жϺ���
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//�ж��жϱ�־λ
//	{
//	
//		Num ++;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//����ж�λ
//	}
//}

