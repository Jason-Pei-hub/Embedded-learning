//防止头文件重复展开
#ifndef __BEEP_H
#define __BEEP_H

#include "main.h"

#define BEEP_ON GPIO_WriteBit(GPIOC,GPIO_Pin_0,Bit_RESET)
#define BEEP_OFF GPIO_WriteBit(GPIOC,GPIO_Pin_0,Bit_SET)
#define BEEP_TURN GPIOC->ODR ^=0x1<<0
	
//函数的外部声明
void BEEP_Config();

#endif
