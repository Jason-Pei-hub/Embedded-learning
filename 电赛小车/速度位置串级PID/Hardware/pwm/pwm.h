#ifndef __pwm_H
#define __pwm_H
#include "stm32f10x.h" 
#include "sys.h" 

void Pwm_Init(u16 arr,u16 psc);
void Pwm_Out1(int Duty_cycle);
void Pwm_Out2(int Duty_cycle);


#endif

