#include "main.h"  

int main(void)
{
	//LED1 PE2 推挽输出
	//配置IO口步骤
	//step1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	//step2.配置IO口模式
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.初始化IO口
	GPIO_Init(GPIOE,&GPIO_InitSTRUCT);
	
	//PE2输出低电平
	GPIO_WriteBit(GPIOE,GPIO_Pin_2,Bit_RESET);
	while(1)
	{
		
	}
}
