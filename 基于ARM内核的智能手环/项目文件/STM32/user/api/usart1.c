#include "usart1.h"

void USART1_Config(u32 brr)
{
	//step1.初始化IO口 PA9，PA10
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//step2.初始化USART1
	//1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//2.配置模式
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = brr;//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//失能硬件流控制
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//停止位1位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据位8位
	//3.初始化
	USART_Init(USART1,&USART_InitStruct);
	//4.使能
	USART_Cmd(USART1,ENABLE);
}


void USART1_SendCh(char data)
{
	//判断上次发送是否完成
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == 0);
	USART_SendData(USART1,data);
}

void USART1_SendStr(char *p)
{
	while(*p != '\0')
	{
	  USART1_SendCh(*p);
		p++;
	}
}