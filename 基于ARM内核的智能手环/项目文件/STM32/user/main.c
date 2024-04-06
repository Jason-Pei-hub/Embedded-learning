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

	if(!B_Reverse)   //渐亮
	{
		tem++;					//该变量会从0~BreatheMax循环，代表PWM的周期
		if(tem > BreatheMax)
		{
			tem = 0;
			Low_Time++;  				//每BreatheMax * 10us自加1
			if(Low_Time >= BreatheMax) //限制加到BreatheMax之后跳到渐灭
			{
				B_Reverse = 1;	
			}
		}	
	}
	else		//渐灭
	{
		tem++;
		if(tem > BreatheMax)
		{
			tem = 0;
			Low_Time--;		 //每BreatheMax * 10us自减1
			if(Low_Time < 0) //限制减到0之后回到渐亮
			{
				B_Reverse = 0;
			}
		}	
	}

	(tem > BreatheMax - Low_Time)?LED2_OFF:LED2_ON; //如果？前条件成立，执行(LED0 = 0)，否则执行(LED0 = 1)
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
	
	MPU_Init();//心率模块初始化
	CountStepInit();//计步函数初始化

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
