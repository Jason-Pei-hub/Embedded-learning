#ifndef __pid_H
#define __pid_H
#include "stm32f10x.h" 
#include "sys.h" 

extern int err_sum;

void Limit(int *Duty_cycle,int Amplitude);
int GFP_abs (int p);
int PID_Position(int expect_position,int current_position);
int16_t PID_Speed(int16_t speed,int16_t encoder);
#endif

