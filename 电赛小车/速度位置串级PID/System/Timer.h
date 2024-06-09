#ifndef __Timer_H
#define __Timer_H
#include "stm32f10x.h" 
#include "sys.h" 

extern float expect_speed;//期望速度	(几圈/s)
extern int expect_position;//期望圈数	(几圈)

extern float Speed;
extern int32_t count;
extern uint8_t stop_flag;
void Timer_Init(void);


#endif
