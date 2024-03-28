#include "main.h"  
extern const unsigned char gImage_yuanshen1[45000];

extern const unsigned char gImage_images[153600];
extern const unsigned char gImage_image1[72320];

int main(void)
{
	LED_Config();
	RGB_Config();
	KET_Config();
	BEEP_Config();
	TFTLCD_Init();
	
	//LCD_Display_Dir(1);	
	
	SysTick_Config(72000);
	USART1_Config(115200);
	
	LEDR_OFF;LEDG_OFF;LEDB_OFF;
  u8 key_flag = 0;
	//u8 arr[20] = "Ƕ��ʽ�������";
//	u8 arr1[20] = "��Һ�";
//	u8 arr6[20] = "33��";
//	u8 arr5[20] = "Jason_Pei";
//	u8 arr2[50] = "���ע�ҵ�GitHub���һ�ÿ�ո���ѧϰ�ʼ�";
//	u8 arr3[50] = "https://github.com/Jason-Pei-hub";
	//int i = 0;
	LCD_ShowStringAndHz(20,20,1000,20,16,(u8 *)"��6��",0,BLACK);
	LCD_ShowStringAndHz(20,40,1000,20,16,(u8 *)"Ƕ��ʽ2��",0,BLACK);
	LCD_ShowStringAndHz(20,60,1000,20,16,(u8 *)"������",0,BLACK); 
	LCD_ShowStringAndHz(20,80,1000,20,16,(u8 *)"�������˳��ϲ����  ��",0,0X01CF);
  LCD_ShowPicture(90,110,150,150,(u8*)gImage_yuanshen1);
	
	//LCD_ShowStringAndHz(20,40,100,20,16,arr1,0,BLACK);
	//LCD_ShowPicture(0,0,320,240,(u8*)gImage_images);����ͼƬ
//	LCD_Fill(0,0,320,240,BLACK);
//	LCD_ShowStringAndHz(135,10,1000,20,16,arr1,0,WHITE);
//	LCD_ShowStringAndHz(140,30,1000,20,16,arr6,0,WHITE);
//	LCD_ShowStringAndHz(125,50,1000,20,16,arr5,0,WHITE);
//	LCD_ShowStringAndHz(10,70,1000,20,16,arr2,0,WHITE);
//	LCD_ShowStringAndHz(30,90,1000,20,16,arr3,0,DARKBLUE);

//	LCD_ShowStringAndHz(10,20,1000,20,16,arr1,0,WHITE );
//	LCD_ShowStringAndHz(10,40,1000,20,16,arr6,0,WHITE );
//	LCD_ShowStringAndHz(10,60,1000,20,16,arr5,0,WHITE );
//	LCD_ShowStringAndHz(10,80,1000,20,16,arr2,0,WHITE );
//	LCD_ShowString(10,160,100,20,16,arr3,DARKBLUE);
//LCD_ShowPicture(0,110,320,113,(u8*)gImage_image1);
	
	while(1)
	{
		//����1 ״ָ̬ʾ��
		if(LED1_TIME >= 500)
		{
			LED1_TURN;
			LED1_TIME = 0;
			//USART1_SendStr(arr);
		}

	}
	
}
