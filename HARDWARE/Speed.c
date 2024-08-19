#include "stm32f10x.h"                  // Device header
#include "oled.h"

extern int8_t Speed1;
extern int8_t Speed2;
extern int8_t Speed3;
extern int8_t Speed4;
extern int8_t snum;

void speed_add(void)
{
		Speed1+=snum;
		Speed2+=snum;
		Speed3+=snum;
		Speed4+=snum;
}

void speed_dec(void)
{
		Speed1-=snum;
		Speed2-=snum;
		Speed3-=snum;
		Speed4-=snum;
}
void speed_Hmax(void)
{
		Speed1=90;
		Speed2=90;
		Speed3=90;
		Speed4=90;
}
void speed_Lmax(void)
{
		Speed1=-90;
		Speed2=-90;
		Speed3=-90;
		Speed4=-90;
}

void OLED_ShowSpeed(void)
{
	OLED_ShowSignedNum(1,8,Speed1,3);
	OLED_ShowSignedNum(2,8,Speed2,3);
	OLED_ShowSignedNum(3,8,Speed3,3);
	OLED_ShowSignedNum(4,8,Speed4,3);
}

void Speedzf(void)
{
	if (Speed1>0)
		{
		Motor_Setspeed(Speed1,Speed2,Speed3,Speed4);
		}
		else
		{
			Motor_Setspeed(-Speed1,-Speed2,-Speed3,-Speed4);
		}
}


