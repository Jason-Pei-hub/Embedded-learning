//防止头文件重复展开
#ifndef __DELAY_H
#define __DELAY_H

#include "main.h"   

extern u32 LED1_TIME;
extern u8 key_flag_plus;	
extern u32 DHT11_time;

//函数的外部声明
void Delay_lus(void);
void Delay_us(uint32_t time);
void Delay_ms(uint32_t time);
u8 KEY_Check_Plus(void);
void SysTick_Handler(void);


#endif
