#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);//TIM2是APB1的外设
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//重映射打开AFIO时钟
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//部分重映射，把PA0换到PA15,下面的引脚需要改成初始PA15
	
	//初始化GPIO口	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出，才能把PWM从GPIO输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);//推挽输出，50MHz

	TIM_InternalClockConfig(TIM8);//选择使用内部时钟，上电默认是这个，因此可以不写
	
	TIM_DeInit(TIM8);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//时基单元参数如下
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//一分频，就是不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//自动重装器的值ARR，72M/(ARR+1)/(PSC+1)
	TIM_TimeBaseInitStructure.TIM_Prescaler=36-1;//预分频器的值PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器的值，高级定时器才有用
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStructure);//初始化时基单元,会触发一个事件或中断

	/*计算公式,根据想要的频率和占空比和分辨率就可以算
	频率F=CK_PSC/(PSC+1)/(ARR+1)
	占空比：D=CCR/(ARR+1)
	分辨率：R=1/(ARR+1)
	*/
  
	//初始化输出比较通道，TIM2的OC1口，根据引脚复用表查看输出的GPIO口
	TIM_OCInitTypeDef TIM_OCInitStruture;
	TIM_OCStructInit(&TIM_OCInitStruture);//赋初始值，防止用高级定时器错误
	TIM_OCInitStruture.TIM_OCMode=TIM_OCMode_PWM2;//设置PWM1模式
	TIM_OCInitStruture.TIM_OCPolarity=TIM_OCPolarity_Low;//选择高极性
	TIM_OCInitStruture.TIM_OutputState=TIM_OutputState_Enable;//使能
	TIM_OCInitStruture.TIM_Pulse=0;//设置CCR，捕获比较寄存器
	
	TIM_OC1Init(TIM8,&TIM_OCInitStruture);//PWM输出到1通道ch1
	TIM_OC2Init(TIM8,&TIM_OCInitStruture);//PWM输出到2通道ch2
	TIM_OC3Init(TIM8,&TIM_OCInitStruture);//PWM输出到3通道ch3
	TIM_OC4Init(TIM8,&TIM_OCInitStruture);//PWM输出到4通道ch4
	
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	TIM_ARRPreloadConfig(TIM8, ENABLE); 
	TIM_Cmd(TIM8,ENABLE);//开启定时器
}

void PWM_SetCompare1(uint16_t Compare)//可以更改CCR的值，达到PWM更改的效果
{
	TIM_SetCompare1(TIM8,Compare);
}

void PWM_SetCompare2(uint16_t Compare)//可以更改CCR的值，达到PWM更改的效果
{
	TIM_SetCompare2(TIM8,Compare);
}

void PWM_SetCompare3(uint16_t Compare)//可以更改CCR的值，达到PWM更改的效果
{
	TIM_SetCompare3(TIM8,Compare);
}
void PWM_SetCompare4(uint16_t Compare)//可以更改CCR的值，达到PWM更改的效果
{
	TIM_SetCompare4(TIM8,Compare);
}