#include "stm32f10x.h"                  // Device header
#include "PWM.h"


/*
		电机1		电机2


		电机3		电机4

*/
/*					PWM接口         编码器接口
1  B9、B8			C6      		A15、B3
2  A5、A4			C7				A6、A7
3  C2、C3		  C8				B6、B7
4  B0、B1		  C9				A0、A1
*/

//3号电机不能按照控制运行

void Motor_Init(viod)
{
	//电机方向控制角
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);//推挽输出，50MHz
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_8;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_4;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	PWM_Init();
}

void Moto1Forward(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_9,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_SET);
}

void Moto2Forward(void)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_SET);
}

void Moto3Forward(void)
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_SET);
}

void Moto4Forward(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
}

void Moto1Stop(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_9,Bit_RESET);
	
}

void Moto2Stop(void)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_RESET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);
}
void Moto3Stop(void)
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_RESET);
	GPIO_WriteBit(GPIOC,GPIO_Pin_2,Bit_RESET);
}

void Moto4Stop(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);
}

void Moto1Back(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_9,Bit_SET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET);
}

void Moto2Back(void)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);
}

void Moto3Back(void)
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_2,Bit_SET);
	GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_RESET);
}

void Moto4Back(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);
}


void Move_Forward(void)
{
	Moto1Forward();
	Moto2Forward();
	Moto3Forward();
	Moto4Forward();
}

void Move_Back(void)
{
	Moto1Back();
	Moto2Back();
	Moto3Back();
	Moto4Back();
}

void Move_Right(void)
{
	Moto2Back();
	Moto1Forward();
	Moto3Back();
	Moto4Forward();
}

void Move_Left(void)
{
	Moto1Back();
	Moto2Forward();
	Moto4Back();
	Moto3Forward();
}

void Move_FR(void){
	Moto1Forward();
	Moto2Stop();
	Moto3Stop();
	Moto4Forward();
}

void Move_BL(void){
	Moto1Back();
	Moto2Stop();
	Moto3Stop();
	Moto4Back();
}

void Move_FL(void){	
  Moto1Stop();
	Moto2Forward();
	Moto3Forward();
	Moto4Stop();
}

void Move_BR(void){
	
  Moto1Stop();
	Moto2Back();
	Moto3Back();
	Moto4Stop();
}

void Move_LS(void){
  Moto1Back();
	Moto2Forward();
	Moto3Back();
	Moto4Forward();
}

void Move_RS(void){
	Moto1Forward();
  Moto2Back();
	Moto3Forward();
	Moto4Back();
}

void Motor_Setspeed(int8_t Speed1,int8_t Speed2,int8_t Speed3,int8_t Speed4)//更改PWM，设置速度
{
	if(Speed1>0)
	{
		Moto1Forward();
		PWM_SetCompare1(Speed1);
	}
	else if(Speed1<0)
	{
		Moto1Back();
		PWM_SetCompare1(-Speed1);
	}
	else
	{
		Moto1Stop();
	}
	
	if(Speed2>0)
	{
		Moto2Forward();
		PWM_SetCompare2(Speed2);
	}
	else if(Speed2<0)
	{
		Moto2Back();
		PWM_SetCompare2(-Speed2);
	}
	else
	{
		Moto2Stop();
	}
	
	
	if(Speed3>0)
	{
		Moto3Forward();
		PWM_SetCompare3(Speed3);
	}
	else if(Speed3<0)
	{
		Moto3Back();
		PWM_SetCompare3(-Speed3);
	}
	else
	{
		Moto3Stop();
	}
	
	
	if(Speed4>0)
	{
		Moto4Forward();
		PWM_SetCompare4(Speed4);
	}
	else if(Speed4<0)
	{
		Moto4Back();
		PWM_SetCompare4(-Speed4);
	}
	else
	{
		Moto4Stop();
	}
//	PWM_SetCompare2(Speed2);
//	PWM_SetCompare3(Speed3);
//	PWM_SetCompare4(Speed4);
}
//void Motor_Setspeed2(int8_t Speed)
//{
//	if (Speed>=0)//正转
//	{
//		Moto2Forward();
//		PWM_SetCompare1(Speed);
//	}
//	else//反转
//	{
//		Moto2Back();
//		PWM_SetCompare1(-Speed);
//	}
//}

//void Motor_Setspeed1(int8_t Speed)
//{
//	if (Speed>=0)//正转
//	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_8);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
//		PWM_SetCompare3(Speed);
//	}
//	else//反转
//	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_9);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
//		PWM_SetCompare3(-Speed);
//	}
//}
//void Motor_Setspeed3(int8_t Speed)
//{
//	if (Speed>=0)//正转
//	{
//		GPIO_SetBits(GPIOC,GPIO_Pin_2);
//		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
//		PWM_SetCompare3(Speed);
//	}
//	else//反转
//	{
//		GPIO_SetBits(GPIOC,GPIO_Pin_3);
//		GPIO_ResetBits(GPIOC,GPIO_Pin_2);
//		PWM_SetCompare3(-Speed);
//	}
//}

//void Motor_Setspeed4(int8_t Speed)
//{
//	if (Speed>=0)//正转
//	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_0);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
//		PWM_SetCompare3(Speed);
//	}
//	else//反转
//	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_0);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
//		PWM_SetCompare3(-Speed);
//	}
//}
