#include "main.h"  

#define BreatheMax 280
#define HOUR 17
#define MIN 55
#define CHOUR 17
#define CMIN 56
#define TSTEP 100

void BreatheLed(void)
{
	static unsigned char B_Reverse= 0;
	static int Low_Time = 0;
	static int tem = 0;

	if(!B_Reverse)   //����
	{
		tem++;					//�ñ������0~BreatheMaxѭ��������PWM������
		if(tem > BreatheMax)
		{
			tem = 0;
			Low_Time++;  				//ÿBreatheMax * 10us�Լ�1
			if(Low_Time >= BreatheMax) //���Ƽӵ�BreatheMax֮����������
			{
				B_Reverse = 1;	
			}
		}	
	}
	else		//����
	{
		tem++;
		if(tem > BreatheMax)
		{
			tem = 0;
			Low_Time--;		 //ÿBreatheMax * 10us�Լ�1
			if(Low_Time < 0) //���Ƽ���0֮��ص�����
			{
				B_Reverse = 0;
			}
		}	
	}

	(tem > BreatheMax - Low_Time)?LED2_OFF:LED2_ON; //�����ǰ����������ִ��(LED0 = 0)������ִ��(LED0 = 1)
}



int main(void)
{

	
	LED_Config();
	
	
	RGB_Config();
	KEY_Config();
	BEEP_Config();
  TFTLCD_Init();
	ADC2_Config();
	RTC_Configuration();
  USART1_Config(115200);
	
	MPU_Init();//����ģ���ʼ��
	CountStepInit();//�Ʋ�������ʼ��

	//LCD_Display_Dir(1);	

	SysTick_Config(72000);
	
	Sensor_Init();
	
//	u8 buf[24] = {0};



 
	
//	DaiJi();

	while(1)
	{
		
		
		BreatheLed();
		
		showbiaopan(HOUR,MIN);
	
	}
	
}
