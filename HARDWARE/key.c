#include "stm32f10x.h"                  // Device header
#include "delay.h"
//PC5,key0
//A15(key1),C5(key0)
void KEY_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

uint32_t key_Getnum(void)
{
	uint32_t keynum=0;
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)==0)
	{
		delay_ms(10);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)==0);
		delay_ms(10);
		keynum=1;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0)
	{
		delay_ms(10);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0);
		delay_ms(10);
		keynum=2;
	}
	return keynum;
}
	

