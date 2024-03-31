#ifndef _DHT11_H
#define _DHT11_H

#include "main.h"

typedef struct 
{
  u8 hum;
	float tem;
}DHT11;

extern DHT11 dht11;

int DHT11_GetVale();
void DHT11_Config(u8 i);

#define DHT11_H GPIO_WriteBit(GPIOG,GPIO_Pin_11,Bit_SET)
#define DHT11_L GPIO_WriteBit(GPIOG,GPIO_Pin_11,Bit_RESET)

#define DHT11_R GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11)

#endif