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
		DHT11_GetVale();
		sprintf(buf,"%d°„C",(int)dht11.tem);
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
	  if(zy >= 1000000)
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
		DHT11_GetVale();
		sprintf(buf,"%d°„C",(int)dht11.tem);
		printf("%d\r\n",(int)dht11.tem);
		LCD_ShowStringAndHz(180,100,1000,20,16,buf,0,WHITE);
		
		
		

		
	}
	}
	
	

}

void showyemian2()
{
      



}


