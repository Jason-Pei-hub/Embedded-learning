//防止头文件重复展开
#ifndef __LED_H
#define __LED_H
//宏定义
//#define 小名 大名
#define LED1_ON GPIO_WriteBit(GPIOE,GPIO_Pin_2,Bit_RESET)
#define LED1_OFF GPIO_WriteBit(GPIOE,GPIO_Pin_2,Bit_SET)
#define LED2_ON GPIO_WriteBit(GPIOE,GPIO_Pin_3,Bit_RESET)
#define LED2_OFF GPIO_WriteBit(GPIOE,GPIO_Pin_3,Bit_SET)
#define LED3_ON GPIO_WriteBit(GPIOE,GPIO_Pin_4,Bit_RESET)
#define LED3_OFF GPIO_WriteBit(GPIOE,GPIO_Pin_4,Bit_SET)
#define LED4_ON GPIO_WriteBit(GPIOE,GPIO_Pin_5,Bit_RESET)
#define LED4_OFF GPIO_WriteBit(GPIOE,GPIO_Pin_5,Bit_SET)

#define LEDR_ON GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_RESET)
#define LEDR_OFF GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_SET)
#define LEDG_ON GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_RESET)
#define LEDG_OFF GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_SET)
#define LEDB_ON GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET)
#define LEDB_OFF GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET)

#define LED1_TURN GPIOE->ODR ^=0x1<<2
#define LED2_TURN GPIOE->ODR ^=0x1<<3
#define LED3_TURN GPIOE->ODR ^=0x1<<4
#define LEDR_TURN GPIOA->ODR ^=0x1<<6

#include "main.h"   

//函数的外部声明
void LED_Config(void);
void RGB_Config(void);

#endif
