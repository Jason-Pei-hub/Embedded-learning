#ifndef _USART1_H
#define _USART1_H

#include "main.h"


extern u8 recv;

void USART1_SendCh(char data);
void USART1_Config(u32 brr);
void USART1_SendStr(char *p);

#endif
