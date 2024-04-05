#include "led.h"

//��ʼ��LED
void LED_Config(void)
{
	//LED1 PE2 �������
	//����IO�ڲ���
	//step1.��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	//step2.����IO��ģʽ
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.��ʼ��IO��
	GPIO_Init(GPIOE,&GPIO_InitSTRUCT);
	
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	

}
void RGB_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//step2.����IO��ģʽ
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.��ʼ��IO��
	GPIO_Init(GPIOA,&GPIO_InitSTRUCT);
	
	LEDR_OFF;
	LEDG_OFF;
	LEDB_OFF;

}
