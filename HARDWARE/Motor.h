#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);
void Motor_Setspeed1(int8_t Speed);
void Motor_Setspeed2(int8_t Speed);
void Motor_Setspeed3(int8_t Speed);
void Motor_Setspeed4(int8_t Speed);
void Motor_Setspeed(int8_t Speed1,int8_t Speed2,int8_t Speed3,int8_t Speed4);

void Move_Left(void);
void Move_Right(void);
void Move_Back(void);
void Move_Forward(void);
void Move_To(uint8_t *dstntion);
void Move_Stop(void);
void Move_FR(void);
void Move_FL(void);
void Move_BR(void);
void Move_BL(void);
void Move_LS(void);
void Move_RS(void);

void Moto1Forward(void);
void Moto2Forward(void);
void Moto3Forward(void);
void Moto4Forward(void);

void Moto1Back(void);
void Moto2Back(void);
void Moto3Back(void);
void Moto4Back(void);



#endif