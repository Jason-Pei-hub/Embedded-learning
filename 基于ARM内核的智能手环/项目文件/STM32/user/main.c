#include "main.h"  

#define BreatheMax 280
#define HOUR 17
#define MIN 55
#define CHOUR 17
#define CMIN 56

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
	
	//Sensor_Init();
	RGB_Config();
	//KET_Config();
	BEEP_Config();
  TFTLCD_Init();
	//ADC2_Config();
	RTC_Configuration();
  USART1_Config(115200);
	
	//MPU_Init();//����ģ���ʼ��
	//CountStepInit();//�Ʋ�������ʼ��

	//LCD_Display_Dir(1);	

	SysTick_Config(720);
	
	
	
//	u8 buf[24] = {0};




	
	DaiJi();

	while(1)
	{
		
		
		BreatheLed();
		
		showbiaopan(HOUR,MIN);
		//showyemian1(HOUR,MIN,CHOUR,CMIN);
		
		//����1 ״ָ̬ʾ��
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
//			//��ȡ���ٶ�
//			 MPU_Get_Accelerometer(&ax,&ay,&az);
//			//�Ʋ� _ StepCount
//			 CountStep(ax,ay,az);
//		   printf("%d\r\n",StepCount);
//		}
      
		
		
		//����3 ��ȡ��ʪ��
//		if(DHT11_time >= 2000)
//		{
//		  DHT11_time = 0;
//			DHT11_GetVale();
//			//printf("hum = %dHM\r\ntem = %d��C\r\n",dht11.hum,(int)dht11.tem);
//			sprintf(buf,"hum = %dHM\r\ntem = %d��C\r\n",dht11.hum,(int)dht11.tem);
//			LCD_ShowStringAndHz(20,20,1000,20,16,buf,0,BLACK);
//		}
		

	}
	
}
