#include "main.h"  





extern const unsigned char gImage_watch[153600];

int main(void)
{

	
	LED_Config();
	
//	RGB_Config();
//	KET_Config();
//	BEEP_Config();
	TFTLCD_Init();
	ADC2_Config();
	RTC_Configuration();
	
//	LCD_Display_Dir(1);	
	
	SysTick_Config(72000);
	USART1_Config(115200);
	
	u8 buf[24] = {0};
	LCD_ShowPicture(0,0,240,320,(u8*)gImage_watch);
	//LCD_Fill(0,0,240,320,0x2508);
	
//    LCD_ShowPictureWithTransparent(0,0,240,320,(u8*)gImage_2);

float t = 0;
int sx1 = 0;
int sx2 = 0;
int sy1 = 0;
int sy2 = 0;

int sx3 = 0;
int sx4 = 0;
int sy3 = 0;
int sy4 = 0;

int mx1 = 0;
int mx2 = 0;
int my1 = 0;
int my2 = 0;

int mx3 = 0;
int mx4 = 0;
int my3 = 0;
int my4 = 0;

int hx1 = 0;
int hx2 = 0;
int hy1 = 0;
int hy2 = 0;

int hx3 = 0;
int hx4 = 0;
int hy3 = 0;
int hy4 = 0;

u32 time = 0;

	while(1)
	{
		now_time.tm_min += 33;
    now_time.tm_hour += 17;
		
		
		//任务1 状态指示灯
		if(LED1_TIME >= 500)
		{
			LED1_TURN;
			LED1_TIME = 0;
			
			//USART1_SendStr(arr);
			
		}
		
		//秒针
    get_points_on_concentric_circles(120, 160,7,117,now_time.tm_sec%60, &sx3, &sy3, &sx4, &sy4);
		LCD_DrawLine((uint16_t)sx3,(uint16_t)sy3,(uint16_t)sx4,(uint16_t)sy4,0);
		
		//分针
	  get_points_on_concentric_circles(120, 160,30,115,now_time.tm_min%60, &mx1, &my1, &mx2, &my2);
    get_points_on_concentric_circles(120, 160,7,30,now_time.tm_min%60, &mx3, &my3, &mx4, &my4);

    LCD_DrawLine((uint16_t)mx1,(uint16_t)my1,(uint16_t)mx2,(uint16_t)my2,2);
		LCD_DrawLine((uint16_t)mx3,(uint16_t)my3,(uint16_t)mx4,(uint16_t)my4,0);
		
		//时针
	  get_points_on_concentric_circles(120, 160,30,72,now_time.tm_hour%12*5+5*now_time.tm_min/60, &hx1, &hy1, &hx2, &hy2);
    get_points_on_concentric_circles(120, 160,7,30,now_time.tm_hour%12*5+5*now_time.tm_min/60, &hx3, &hy3, &hx4, &hy4);

    LCD_DrawLine((uint16_t)hx1,(uint16_t)hy1,(uint16_t)hx2,(uint16_t)hy2,3);
		LCD_DrawLine((uint16_t)hx3,(uint16_t)hy3,(uint16_t)hx4,(uint16_t)hy4,1);
		//LCD_Draw_Circle((uint16_t)x1,(uint16_t)y1,2);
		
		//LCD_ShowPicture(70,110,100,100,(u8*)gImage_3);
    Delay_ms(900);
		LCD_ShowPicture(0,0,240,320,(u8*)gImage_watch);
		//LCD_ShowPictureWithTransparent(0,0,240,320,(u8*)gImage_2);

		
    if(RTC_Time >= 1000)
		{
		   RTC_Time = 0;
			 time = RTC_GetCounter();
			 
			 now_time = *localtime(&time);
			 printf("%d-%d-%d %d:%d:%d\r\n",now_time.tm_year,now_time.tm_mon,now_time.tm_mday,now_time.tm_hour,now_time.tm_min,now_time.tm_sec);
			
		}
		

		
		
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
