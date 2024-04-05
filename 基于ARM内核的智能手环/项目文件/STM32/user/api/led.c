#include "led.h"

//初始化LED
void LED_Config(void)
{
	//LED1 PE2 推挽输出
	//配置IO口步骤
	//step1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	//step2.配置IO口模式
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.初始化IO口
	GPIO_Init(GPIOE,&GPIO_InitSTRUCT);
	
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	

}
void RGB_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//step2.配置IO口模式
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.初始化IO口
	GPIO_Init(GPIOA,&GPIO_InitSTRUCT);
	
	LEDR_OFF;
	LEDG_OFF;
	LEDB_OFF;

}
