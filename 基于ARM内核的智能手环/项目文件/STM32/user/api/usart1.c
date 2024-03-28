#include "usart1.h"


u8 recv;
void USART1_IRQHandler()
{
	//�ж���ʲô�ж�
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == 1)
	{
	  recv = USART1->DR;
		USART1->DR = recv;
	}
}

void USART1_Config(u32 brr)
{
	//step1.��ʼ��IO�� PA9��PA10
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//step2.��ʼ��USART1
	//1.��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//2.����ģʽ
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = brr;//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ʧ��Ӳ��������
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//ֹͣλ1λ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//����λ8λ
	//3.��ʼ��
	USART_Init(USART1,&USART_InitStruct);
	//4.ʹ��
	USART_Cmd(USART1,ENABLE);
	
	
	//���������ж�
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	//NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	
	NVIC_Init(&NVIC_InitStruct);

	
}


void USART1_SendCh(char data)
{
	//�ж��ϴη����Ƿ����
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

//printf�ض���
int fputc(int d,FILE *f)
{
  USART1_SendCh(d);
	return d;
}
