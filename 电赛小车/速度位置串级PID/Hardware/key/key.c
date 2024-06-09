#include "key.h"
uint8_t keynum=0;
void key_Init(void)
{
	GPIO_InitTypeDef key;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);

	key.GPIO_Mode=GPIO_Mode_IPU;//上拉输入，用来识别按键
	key.GPIO_Pin= GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5;
	key.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOF,&key);
}




