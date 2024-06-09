#ifndef __Timer_H
#define __Timer_H
#include "stm32f10x.h" 
#include "sys.h" 

extern float expect_speed;//�����ٶ�	(��Ȧ/s)
extern int expect_position;//����Ȧ��	(��Ȧ)

extern float Speed;
extern int32_t count;
extern uint8_t stop_flag;
void Timer_Init(void);


#endif
