#include "main.h"  

#define BreatheMax 280
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
	/*
	以渐亮为例：
		函数是10us周期性调用
						tem：	从0~BreatheMax循环递增
		BreatheMax - Low_Time ：随着 Low_Time 的增加，因为BreatheMax是固定的，所以BreatheMax - Low_Time会减少
		例如： Low_Time = 60；BreatheMax - Low_Time = 220，
			则下列语句执行的效果就是：有220 * 10us 的时间语句条件不成立，执行 (LED0 = 1)
									   60*10us  的时间语句条件成立，	 执行 (LED0 = 0)
			灯是低电平点亮，由于高电平时间比低电平多，所以呈现灯较暗的现象，反之则亮
	*/
	(tem > BreatheMax - Low_Time)?LED2_OFF:LED2_ON; //如果？前条件成立，执行(LED0 = 0)，否则执行(LED0 = 1)
}



int main(void)
{

	
	LED_Config();
	
	//Sensor_Init();
	//RGB_Config();
	KET_Config();
	//BEEP_Config();
  //TFTLCD_Init();
	ADC2_Config();
	RTC_Configuration();
  USART1_Config(115200);
	
	//MPU_Init();//心率模块初始化
	//CountStepInit();//计步函数初始化

	//LCD_Display_Dir(1);	

	SysTick_Config(720);
	
	
	
//	u8 buf[24] = {0};
	

// showbiaopan_init();
  u32 time = 0;
	
	int i = 0;
  int p = 0;
	int q = 0;
	
	
	

	while(1)
	{
		BreatheLed();
		time = RTC_GetCounter();
    now_time = *localtime(&time);
		
	//	showbiaopan(22,17);
		
		
		//任务1 状态指示灯
		if(LED1_TIME >= 50000)
		{
			LED1_TURN;
			LED1_TIME = 0;
			
			//USART1_SendStr(arr);
			
		}
		
//		for(i = 0;i <= 1000; i++)
//		{
//		  LED2_ON;
//			Delay_us(i);
//			LED2_OFF;
//			Delay_us(1000-i);
//		}

		
		
		if(on_time >= i&&p == 0&&q == 0)
		{
		  LED3_ON;
			on_time = 0;
			off_time = 0;
			p = 1;
			
		}
		
		if(off_time >= 1000-i&&p == 1&&q == 0)
		{
			
		  LED3_OFF;
			off_time = 0;
			on_time = 0;
			p = 0;
			if(i>=1000)
			{
			  i = 0;
				q = 1;
			}
		  i++;
		}
		
		if(on_time >= i&&p == 0&&q == 1)
		{
		  LED3_OFF;
			on_time = 0;
			off_time = 0;
			p = 1;
			
		}
		
		if(off_time >= 1000-i&&p == 1&&q == 1)
		{
			i++;
		  LED3_ON;
			off_time = 0;
			on_time = 0;
			p = 0;
			if(i>=1000)
		  {
			  i = 0;
				q = 0;
			}
		}
		
//		
//    LED4_ON;
//		LEDR_OFF;

		
//    if(RTC_Time >= 1000)
//		{
//		   RTC_Time = 0;
//			 time = RTC_GetCounter();
//			 
//			 now_time = *localtime(&time);
//			 printf("%d-%d-%d %d:%d:%d\r\n",now_time.tm_year,now_time.tm_mon,now_time.tm_mday,now_time.tm_hour,now_time.tm_min,now_time.tm_sec);
//			
//		}
		
//		if(XINLV_Time >= 1000)
//		{
//		   XINLV_Time = 0;
//			 Sensor();
//			 
//			
//		}
//		if(MPU6050_Time >= 10)
//		{
//		   MPU6050_Time = 0;
//			//获取加速度
//			 MPU_Get_Accelerometer(&ax,&ay,&az);
//			//计步 _ StepCount
//			 CountStep(ax,ay,az);
//		   printf("%d\r\n",StepCount);
//		}
      
		
		
		//任务3 获取温湿度
//		if(DHT11_time >= 2000)
//		{
//		  DHT11_time = 0;
//			DHT11_GetVale();
//			//printf("hum = %dHM\r\ntem = %d°C\r\n",dht11.hum,(int)dht11.tem);
//			sprintf(buf,"hum = %dHM\r\ntem = %d°C\r\n",dht11.hum,(int)dht11.tem);
//			LCD_ShowStringAndHz(20,20,1000,20,16,buf,0,BLACK);
//		}
		

	}
	
}
