#include "beep.h"   

void BEEP_Config()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//step2.����IO��ģʽ
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.��ʼ��IO��
	GPIO_Init(GPIOC,&GPIO_InitSTRUCT);

}
