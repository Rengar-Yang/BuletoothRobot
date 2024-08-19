#include "stm32f10x.h"                  // Device header

void LED_Init(void)
	{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

		
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);//���������50MHz
		
	GPIO_SetBits(GPIOD,GPIO_Pin_2);//Ĭ�Ϲر�
	
	//LED����ʵ�飬IO�����
}
//������дһ�㣬����һ����Ҳ������˸
void LED_ON(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}


void LED_OFF(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
}

		//	GPIO_ResetBits(GPIOD,GPIO_Pin_2);//��PD2д0
//	GPIO_SetBits(GPIOD,GPIO_Pin_2);//д1
//	GPIO_WriteBit(GPIOD,GPIO_Pin_2,Bit_RESET);//д0
//	GPIO_WriteBit(GPIOD,GPIO_Pin_2,Bit_SET);//д1
/*
	delay_init();
	while(1)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		delay_ms(500);
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
		delay_ms(500);
		
	}
	*/