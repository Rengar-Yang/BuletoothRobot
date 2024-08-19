#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);//TIM2��APB1������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//��ӳ���AFIOʱ��
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//������ӳ�䣬��PA0����PA15,�����������Ҫ�ĳɳ�ʼPA15
	
	//��ʼ��GPIO��	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//����������������ܰ�PWM��GPIO���
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);//���������50MHz

	TIM_InternalClockConfig(TIM8);//ѡ��ʹ���ڲ�ʱ�ӣ��ϵ�Ĭ�����������˿��Բ�д
	
	TIM_DeInit(TIM8);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//ʱ����Ԫ��������
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//һ��Ƶ�����ǲ���Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//�Զ���װ����ֵARR��72M/(ARR+1)/(PSC+1)
	TIM_TimeBaseInitStructure.TIM_Prescaler=36-1;//Ԥ��Ƶ����ֵPSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//�ظ���������ֵ���߼���ʱ��������
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStructure);//��ʼ��ʱ����Ԫ,�ᴥ��һ���¼����ж�

	/*���㹫ʽ,������Ҫ��Ƶ�ʺ�ռ�ձȺͷֱ��ʾͿ�����
	Ƶ��F=CK_PSC/(PSC+1)/(ARR+1)
	ռ�ձȣ�D=CCR/(ARR+1)
	�ֱ��ʣ�R=1/(ARR+1)
	*/
  
	//��ʼ������Ƚ�ͨ����TIM2��OC1�ڣ��������Ÿ��ñ�鿴�����GPIO��
	TIM_OCInitTypeDef TIM_OCInitStruture;
	TIM_OCStructInit(&TIM_OCInitStruture);//����ʼֵ����ֹ�ø߼���ʱ������
	TIM_OCInitStruture.TIM_OCMode=TIM_OCMode_PWM2;//����PWM1ģʽ
	TIM_OCInitStruture.TIM_OCPolarity=TIM_OCPolarity_Low;//ѡ��߼���
	TIM_OCInitStruture.TIM_OutputState=TIM_OutputState_Enable;//ʹ��
	TIM_OCInitStruture.TIM_Pulse=0;//����CCR������ȽϼĴ���
	
	TIM_OC1Init(TIM8,&TIM_OCInitStruture);//PWM�����1ͨ��ch1
	TIM_OC2Init(TIM8,&TIM_OCInitStruture);//PWM�����2ͨ��ch2
	TIM_OC3Init(TIM8,&TIM_OCInitStruture);//PWM�����3ͨ��ch3
	TIM_OC4Init(TIM8,&TIM_OCInitStruture);//PWM�����4ͨ��ch4
	
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	TIM_ARRPreloadConfig(TIM8, ENABLE); 
	TIM_Cmd(TIM8,ENABLE);//������ʱ��
}

void PWM_SetCompare1(uint16_t Compare)//���Ը���CCR��ֵ���ﵽPWM���ĵ�Ч��
{
	TIM_SetCompare1(TIM8,Compare);
}

void PWM_SetCompare2(uint16_t Compare)//���Ը���CCR��ֵ���ﵽPWM���ĵ�Ч��
{
	TIM_SetCompare2(TIM8,Compare);
}

void PWM_SetCompare3(uint16_t Compare)//���Ը���CCR��ֵ���ﵽPWM���ĵ�Ч��
{
	TIM_SetCompare3(TIM8,Compare);
}
void PWM_SetCompare4(uint16_t Compare)//���Ը���CCR��ֵ���ﵽPWM���ĵ�Ч��
{
	TIM_SetCompare4(TIM8,Compare);
}