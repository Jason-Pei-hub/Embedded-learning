#include "stm32f10x.h"                  
#include "sys.h" 


/*
	ѡ�õı��������Ϊ13�ߵĻ��������������������ٱ�Ϊ1:30
	ת��һȦ���13*30=390�����塣��Ϊ��ʱ��������
	��Ƶ��������һȦ���390*4=1560�����塣
*/

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//�жϷ���
	
	OLED_Init();		//OLED��ʼ��
	Timer_Init();		//��ʱ����ʼ��
	Pwm_Init(7200,1);   //���pwm��ʼ��
	motor_Init();		//��������ʼ��
	Encoder_Init();		//��������ʼ��
	USART2_Init(115200);//���Դ��ڳ�ʼ��
	key_Init();			//������ʼ��
	
  OLED_ShowString(1,1,"read_l:");
	OLED_ShowString(2,1,"read_r:");
	OLED_ShowString(3,1,"out_l:");
	OLED_ShowString(4,1,"out_r:");
	
	expect_speed= 15;//�����ٶ�	(��Ȧ/s)
  expect_position= 5;//����Ȧ��	(��Ȧ)

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
