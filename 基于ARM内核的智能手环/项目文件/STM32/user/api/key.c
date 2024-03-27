#include "key.h"

void KET_Config()
{
	//KEY1 --paPA0
	//KEY2 --paPC5
	//KEY3 --paPC6
  //浮空输入
	//step1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA,ENABLE);
	
	//step2.配置IO口模式
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.初始化IO口
	GPIO_Init(GPIOA,&GPIO_InitSTRUCT);
	
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	
	GPIO_Init(GPIOC,&GPIO_InitSTRUCT);
}

//按键检测
uint8_t KEY_Check(void)
{
	//按键检测
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
		{
			Delay_ms(15);
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
			{
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
				{}
				return 1;
			}
		}
		return 0;
}
