#include "stm32f10x.h"
#include "delay.h"
#include "LED.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "oled.h"
#include "zhongduan.h"
#include "Encoder.h"
#include "Timer.h"
#include "Motor.h"
#include "Key.h"
#include "remote.h"
#include "Speed.h"
#include "usart2.h"

uint8_t KeyNum;
int8_t Speed1=0;
int8_t Speed2=0;
int8_t Speed3=0;
int8_t Speed4=0;

uint8_t key_remote;
int8_t snum=5;
uint32_t keynum=0;

uint16_t Num;

int main()
{
	LED_Init();
	delay_init();
	//Usart2_Init(9600);
	USART2_Init(9600);
	KEY_Init();
	zhongduan_Init();

	OLED_Init();
	uart_init(9600);	 			//串口初始化9600

//	Timer_Init();
	OLED_ShowString(1,1,"Speed1:");
	OLED_ShowString(2,1,"Speed2:");
	OLED_ShowString(3,1,"Speed3:");
	OLED_ShowString(4,1,"Speed4:");
	Remote_Init();
	Motor_Init();
	
	while(1)
{
	key_remote=Remote_Scan();	
		if(key_remote)
		{	 	  
			switch(key_remote)
			{
				case 0:{											//ERROR,用来设置第二速度
		Speed1=50;
		Speed2=50;
		Speed3=50;
		Speed4=50;
		Speedzf();
    OLED_ShowSpeed();
				}break;		   
				case 162:{{ 								//POWER
		Speed1=30;
		Speed2=30;
		Speed3=30;
		Speed4=30;
		Speedzf();
    OLED_ShowSpeed();					
				}break;	    								
				
				case 98:										//up
		{	delay_ms(20);
					speed_add();
		if (Speed1>=90)
		{
			speed_Hmax();
		}
		Speedzf();
		OLED_ShowSpeed();
		}break;	    
		
				case 168:{										//down
				delay_ms(20);
				speed_dec();
		if (Speed1<=-90)
		{
			speed_Lmax();
		}
		Speedzf();
		OLED_ShowSpeed();
				}break;		
				
				case 2:{											//play
		Speed1=0;Speed2=0;Speed3=0;Speed4=0;
		Motor_Setspeed(Speed1,Speed2,Speed3,Speed4);
		OLED_ShowSpeed();
					
				}break;		 
//				case 226:str="ALIENTEK";break;		  
				
				case 194:{										//RIGHT控制单次增加的速度
				snum+=1;
				delay_ms(50);
				if (snum>=5){snum=5;}
				}break;	   
				
				case 34:{//LEFT控制单次减少的速度
				snum-=1;
				delay_ms(50);
				if (snum<=1){snum=1;}
				}break;	
				case 224:{Move_LS();Speedzf();OLED_ShowSpeed();}break;		  //VOL-,Speedzf是判断是否大于或者小于0
				case 144:{Move_RS();Speedzf();OLED_ShowSpeed();}break;		    //VOL+
			case 104:{Move_FL();Speedzf();OLED_ShowSpeed();}break;		  	//1
			case 152:{Move_Forward();Speedzf();OLED_ShowSpeed();}break;	//2   
				case 176:{Move_FR();Speedzf();OLED_ShowSpeed();}break;	    	//3
				case 48:{Move_Left();Speedzf();OLED_ShowSpeed();}break;		    //4
				
				case 24:{Speed1=0;Speed2=0;Speed3=0;Speed4=0;
		Motor_Setspeed(Speed1,Speed2,Speed3,Speed4);
		OLED_ShowSpeed();}break;		    //5
				
				case 122:{Move_Right();Speedzf();OLED_ShowSpeed();}break;		  //6
				case 16:{Move_BL();Speedzf();OLED_ShowSpeed();}break;			   //7					
				case 56:{Move_Back();Speedzf();OLED_ShowSpeed();}break;	 //8
				case 90:{Move_BR();Speedzf();OLED_ShowSpeed();}break;//9
				
				case 66:{delay_ms(20);																//0
					speed_add();
		if (Speed1>=90)
		{
			speed_Hmax();
		}
		OLED_ShowSpeed();}break;
//				case 82:str="DELETE";break;		 
			}
		}
		}else delay_ms(10);	
}

}

//void USART2_IRQHandler(void)
//{
//	u8 res;
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断
//	{
//		Speed1=20;Speed2=20;Speed3=20;Speed4=20;
//		OLED_ShowSpeed();
//		OLED_ShowString(4,1,"Speed4:");
//		res = USART_ReceiveData(USART1);
//		switch (res)
//		{
//			case 0x00: {Motor_Setspeed(0,0,0,0);} break;//停止
//			case 0x01: {Move_FL();Speedzf();OLED_ShowSpeed();} break;//前进
//			case 0x02: {Move_Back();Speedzf();OLED_ShowSpeed();} break;//后退
//			case 0x03: {Move_Left();Speedzf();OLED_ShowSpeed();} break;//左转
//			case 0x04: {Move_Right();Speedzf();OLED_ShowSpeed();} break;//右转
//		}
//	}
//}

//void TIM2_IRQHandler(void)//中断函数
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//判断中断标志位
//	{
//	
//		Num ++;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清空中断位
//	}
//}

/*OLED显示代码
	OLED_ShowChar(1,1,'A');
	OLED_ShowNum(2,1,12345,5);
	OLED_ShowSignedNum(2,7,-66,2);
	OLED_ShowHexNum(3,1,0XAA55,4);
	OLED_ShowBinNum(4,1,0xAA55,16);
*/



/*按键实验的循环执行主函数
keynum=key_Getnum();
	if (keynum==0){
	LED_ON();
	}
	if (keynum==1){
	LED_OFF();
	}
	
	 LCD_ShowNum(30,40,keynum,2,16);
	 LCD_ShowString(30,130,200,12,12,"2023/3/15");
	*/


/*
 int main(void)
 { 
	u8 x=0;
	u8 lcd_id[12];			//存放LCD ID字符串	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
	POINT_COLOR=RED; 
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。				 	
  	while(1) 
	{		 
		switch(x)
		{
			case 0:LCD_Clear(WHITE);break;
			case 1:LCD_Clear(BLACK);break;
			case 2:LCD_Clear(BLUE);break;
			case 3:LCD_Clear(RED);break;
			case 4:LCD_Clear(MAGENTA);break;
			case 5:LCD_Clear(GREEN);break;
			case 6:LCD_Clear(CYAN);break;

			case 7:LCD_Clear(YELLOW);break;
			case 8:LCD_Clear(BRRED);break;
			case 9:LCD_Clear(GRAY);break;
			case 10:LCD_Clear(LGRAY);break;
			case 11:LCD_Clear(BROWN);break;
		}
		POINT_COLOR=RED;	  
		LCD_ShowString(30,40,200,24,24,"Mini STM32 ^_^");	
		LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
		LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
 		LCD_ShowString(30,110,200,16,16,lcd_id);		//显示LCD ID	      					 
		LCD_ShowString(30,130,200,12,12,"2014/3/7");	      					 
	    x++;
		if(x==12)x=0;
		LED0=!LED0;	 
		delay_ms(1000);	
	} 
}
*/	


