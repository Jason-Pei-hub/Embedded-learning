#include "stm32f10x.h"                  
#include "sys.h" 


/*
	选用的编码器电机为13线的霍尔编码器电机，电机减速比为1:30
	转动一圈输出13*30=390个脉冲。因为定时器采用四
	倍频计数，则一圈输出390*4=1560个脉冲。
*/

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//中断分组
	
	OLED_Init();		//OLED初始化
	Timer_Init();		//定时器初始化
	Pwm_Init(7200,1);   //电机pwm初始化
	motor_Init();		//电机方向初始化
	Encoder_Init();		//编码器初始化
	USART2_Init(115200);//调试串口初始化
	key_Init();			//按键初始化
	
  OLED_ShowString(1,1,"read_l:");
	OLED_ShowString(2,1,"read_r:");
	OLED_ShowString(3,1,"out_l:");
	OLED_ShowString(4,1,"out_r:");
	
	expect_speed= 15;//期望速度	(几圈/s)
  expect_position= 5;//期望圈数	(几圈)

while (1) 
	{
		
//	while (1)
//	{
//		
//		OLED_ShowSignedNum(1,9,Speed,2);
//		OLED_ShowSignedNum(2,9,count,2);
//		
//		UsartPrintf(USART2,"%f,%d\r\n",Speed,count);
//		
//	
}
}
