#include "stm32f10x.h"                  // Device header


void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//TIM2是APB1的外设
	
	TIM_InternalClockConfig(TIM2);//选择使用内部时钟，上电默认是这个，因此可以不写
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//时基单元参数如下
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//一分频，就是不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period=10000-1;//自动重装器的值ARR，72M/(ARR+1)/(PSC+1)
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;//预分频器的值PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器的值，高级定时器才有用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化时基单元,会触发一个事件或中断

	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//用于使能中断

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//选择分组二
	
	//中断配置
	NVIC_InitTypeDef NVIC_InitStrcture;
	
	NVIC_InitStrcture.NVIC_IRQChannel=TIM2_IRQn;//TIM2的中断通道
	NVIC_InitStrcture.NVIC_IRQChannelCmd=ENABLE;//
	NVIC_InitStrcture.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStrcture.NVIC_IRQChannelSubPriority=1;//相应优先级
	NVIC_Init(&NVIC_InitStrcture);
	
	TIM_Cmd(TIM2,ENABLE);//开启定时器
}

//void TIM2_IRQHandler(void)//中断函数
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//判断中断标志位
//	{
//	
//		Num ++;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清空中断位
//	}
//}

