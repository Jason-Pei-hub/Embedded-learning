#ifndef __myusart_H
#define __myusart_H
#include "stm32f10x.h" 
#include "sys.h" 
#include <stdarg.h>
#include <stdio.h>

void USART2_Init(u32 BoTeLv);
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);



#endif

