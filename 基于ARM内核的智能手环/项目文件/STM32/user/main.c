#include "main.h"  

int main(void)
{
	//LED1 PE2 �������
	//����IO�ڲ���
	//step1.��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	//step2.����IO��ģʽ
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.��ʼ��IO��
	GPIO_Init(GPIOE,&GPIO_InitSTRUCT);
	
	//PE2����͵�ƽ
	GPIO_WriteBit(GPIOE,GPIO_Pin_2,Bit_RESET);
	while(1)
	{
		
	}
}
