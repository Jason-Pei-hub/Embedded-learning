#include "yemian1.h"

void showyemian1(int hour,int min,int chour,int cmin)
{
	u32 time = 0;
	char timestr[20];
	char daystr[20];
	char cstr[20];
	u8 buf[24] = {0};
	int flag = 0;
	
  LCD_ShowPicture(0,0,240,320,(u8*)gImage_zhuye);
	
	time = RTC_GetCounter();
	now_time = *localtime(&time);
	now_time.tm_min += min;
  now_time.tm_hour += hour;
	
	sprintf(timestr, "%d:%d", now_time.tm_hour, now_time.tm_min);
	sprintf(daystr, "%d-%d-%d", now_time.tm_year+1954, now_time.tm_mon+4,now_time.tm_mday+6);
	sprintf(cstr, "%d:%d",chour, cmin);
	
	LCD_ShowString(170,45,1000,40,12,(u8*)daystr,0xFC89);
	LCD_ShowStringAndHz(160,65,1000,40,24,(u8*)timestr,0,WHITE);
	LCD_ShowStringAndHz(24,169,1000,40,16,(u8*)cstr,0,WHITE);
	
  	DHT11_time = 0;
		DHT11_GetValue();
		sprintf(buf,"%d°C",(int)dht11.tem);
		LCD_ShowStringAndHz(180,100,1000,20,16,buf,0,WHITE);

	while(1)
	{
		if(!strcmp(timestr,cstr)&&flag==0)
		{
		while(1)
		{
		  BEEP_ON;
		  Delay_ms(100);
			BEEP_OFF;
			if(KEY_Check())
			{
			  flag = 1;
				break;
			}
		}
		}
		BreatheLed();
	  if(zy >= 10000)
	{
		 zy = 0;
		 flag = 0;
		 time = RTC_GetCounter();
		 now_time = *localtime(&time);
		 now_time.tm_min += min;
     now_time.tm_hour += hour;
		
		 sprintf(timestr, "%d:%d", now_time.tm_hour, now_time.tm_min);
		
		 LCD_ShowStringAndHz(160,65,1000,40,24,(u8*)timestr,0,WHITE);
		
		 LEDB_ON;
		
		
		DHT11_time = 0;
		DHT11_GetValue();
		sprintf(buf,"%d°C",(int)dht11.tem);
		printf("%d\r\n",(int)dht11.tem);
		LCD_ShowStringAndHz(180,100,1000,20,16,buf,0,WHITE);
		
		
		

		
	}
	}
	
	

}

void showyemian2()
{
   LCD_ShowPicture(0,0,240,320,(u8*)gImage_ymxl);
   LCD_ShowString(21,262,56,16,16,(u8*)"BPM:",WHITE);
	 LCD_ShowString(21,282,56,16,16,(u8*)"IBI:",WHITE);
	while(1)
	{
		BreatheLed();
	  if(XINLV_Time >= 100)
		{
		   XINLV_Time = 0;
			 Sensor();
		}
	}
		

}

void showyemian3(int n)
{
	  u8 arr[20];
	  LCD_ShowxNum(27,105,0,6,24,0);
    LCD_ShowPicture(0,0,240,320,(u8*)gImage_ymyd);
  	LCD_DrawLine3(32,144,214,144,5);
    while(1)
		{
		  BreatheLed();
			if(MPU6050_Time >= 10)
		{
		   MPU6050_Time = 0;
			//获取加速度
			 MPU_Get_Accelerometer(&ax,&ay,&az);
			//计步 _ StepCount
			 CountStep(ax,ay,az);
		   printf("%d\r\n",StepCount);
			
			 
		}
		if(MPU6050_Time2 >= 2000)
		{
			LCD_ShowxNum(20,105,StepCount,5,24,0);
			sprintf(arr,"%.2f M",StepCount*0.3);
			
			LCD_ShowString(147,120,50,16,16,arr,WHITE);
			
			LCD_ShowxNum(27,195,n,6,16,0);
		  MPU6050_Time2 = 0;
			LCD_DrawLine3(32,144,214,144,5);
			if(StepCount <= n)
			{
			  LCD_DrawLine4(32,144,32+StepCount*182/n,144,5);
				
			}else
			{
			  LCD_ShowString(30,235,50,16,16,"Finish",0xFC89);
				LCD_DrawLine4(32,144,214,144,5);
			}
		
			
		}
		}
}

void showyemian4(int n)
{
  LCD_ShowPicture(0,0,240,320,(u8*)gImage_ymwd);
	u8 buf[24] = {0};
	u8 buf1[24] = {0};
	while(1)
	{
    BreatheLed();
		
		if(DHT11_time >= 200)
		{
			DHT11_time = 0;
			

			
			DHT11_GetValue();
			LCD_ShowxNum(24,68,dht11.tem,2,24,0);
			LCD_ShowxNum(152,197,dht11.hum,3,16,0);
			
			ADC2_GetValue();
		  LCD_ShowxNum(30,197,illu,4,16,0);
			LCD_ShowxNum(32,279,mq,3,16,0);

		}
		 

		
		
	}
}
