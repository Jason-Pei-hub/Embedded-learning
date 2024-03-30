#include "main.h"  


extern const unsigned char gImage_zhaixiang[20700];
extern const unsigned char gImage_image1[72320];
extern const unsigned char gImage_1[115200];
extern const unsigned char gImage_2[115200];
extern const unsigned char gImage_3[115200];
extern const unsigned char gImage_4[115200];
extern const unsigned char gImage_5[115200];
extern const unsigned char gImage_6[115200];
extern const unsigned char gImage_7[115200];
extern const unsigned char gImage_8[115200];
extern const unsigned char gImage_9[115200];
extern const unsigned char gImage_10[115200];


int main(void)
{
	LED_Config();
	
//	RGB_Config();
//	KET_Config();
//	BEEP_Config();
	TFTLCD_Init();
	
	LCD_Display_Dir(1);	
	
	SysTick_Config(72000);
	USART1_Config(115200);
	
	u8 buf[24] = {0};
	
	LCD_Fill(0,0,320,240,BLACK);
	
//	LEDR_OFF;LEDG_OFF;LEDB_OFF;
//  u8 key_flag = 0;
//	u8 arr[20] = "嵌入式软件二班";
//	u8 arr1[20] = "裴家豪";
//	u8 arr6[10] = "33组";
//	u8 arr5[20] = "Jason_Pei";
//	u8 arr2[50] = "请关注我的GitHub，我会每日更新学习笔记";
//	u8 arr3[50] = "https://github.com/Jason-Pei-hub";
	//int i = 0;

	

//	LCD_ShowStringAndHz(135,10,1000,20,16,arr1,0,WHITE);
//	LCD_ShowStringAndHz(140,30,1000,20,16,arr6,0,WHITE);
//	LCD_ShowStringAndHz(125,50,1000,20,16,arr5,0,WHITE);
//	LCD_ShowStringAndHz(10,70,1000,20,16,arr2,0,WHITE);
//	LCD_ShowStringAndHz(30,90,1000,20,16,arr3,0,DARKBLUE);


//  LCD_ShowPicture(0,110,320,113,(u8*)gImage_image1);
	
	while(1)
	{
		//任务1 状态指示灯
		if(LED1_TIME >= 500)
		{
			LED1_TURN;
			LED1_TIME = 0;
			//USART1_SendStr(arr);
		}
		
		LCD_ShowPicture(85,45,150,150,(u8*)gImage_1);
		Delay_ms(4);       
												
		LCD_ShowPicture(85,45,150,150,(u8*)gImage_2);
		Delay_ms(4);       
												
		LCD_ShowPicture(85,45,150,150,(u8*)gImage_3);
		Delay_ms(4);       
												
		LCD_ShowPicture(85,45,150,150,(u8*)gImage_4);
		Delay_ms(4);       
												
		LCD_ShowPicture(85,45,150,150,(u8*)gImage_5);
		Delay_ms(4);       
												
		LCD_ShowPicture(85,45,150,150,(u8*)gImage_6);
		Delay_ms(4);       
												
		LCD_ShowPicture(85,45,150,150,(u8*)gImage_7);
		Delay_ms(4);       
												
		LCD_ShowPicture(85,45,150,150,(u8*)gImage_8);
		Delay_ms(4);       
												
		LCD_ShowPicture(85,45,150,150,(u8*)gImage_9);
		Delay_ms(4);        
												
		LCD_ShowPicture(85,45,150,150,(u8*)gImage_10);
		Delay_ms(4);  

		
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
