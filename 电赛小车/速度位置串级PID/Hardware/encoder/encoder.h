#ifndef __encoder_H
#define __encoder_H
#include "stm32f10x.h" 
#include "sys.h" 

void Encoder_Init(void);

int32_t Read_Encoder1(void);
int32_t Read_Encoder2(void);

#endif

