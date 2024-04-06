#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"

#define DHT11_H GPIO_WriteBit(GPIOG,GPIO_Pin_11,Bit_SET)
#define DHT11_L GPIO_WriteBit(GPIOG,GPIO_Pin_11,Bit_RESET)
#define DHT11_R GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11)
typedef struct 
{
	u8 hum;
	float tem;
	

}DHT11;


extern DHT11 dht11;
int DHT11_GetValue(void);

#endif
