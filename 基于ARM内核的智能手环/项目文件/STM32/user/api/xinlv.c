#include "stm32f10x.h"
#include "xinlv.h"
#include "stdio.h"
#include "bsp_lcd.h"
#include "timer.h"
#include "adc.h"

void Sensor_Init(void)
{
	Adc_Init();
	TFTLCD_Init();
	TIM3_Int_Init(1999,71);//��ʱ����2ms
	Show_SensorView();
//	/* TIM3 ���¿�ʱ�ӣ���ʼ��ʱ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}

/**���ʼ��*/
                                                                                                                     void Sensor(void)
{	
		LCD_ShowxNum(20,210,BPM,3,24,0);
		Show_Sensor(Signal);
		printf("Signal=%d\r\n",Signal);
		if (QS == true)
		{		
				LCD_ShowxNum(60,242,BPM,3,16,0);
				
				LCD_ShowxNum(60,262,IBI,3,16,0);
				
				QS = false; // reset the Quantified Self flag for next time
					
				//��BPMֵ���з�Χ����
				
		}
}

void Show_SensorView(void)
{    
	
//	Draw_Text_Str(60,150,BLUE,RED,"* BPM: ");	
//	Draw_Text_Str(60,170,BLUE,RED,"* IBI");	  
}

#define HighY 113               //�����ĵ�ͼ�����߶�
#define Min_Sensor_y HighY/1024  //�����ĵ�ͼ����С����
void Show_Sensor(u16 signal)
{
	static u16	rate_y,rate_y_buf,rate_y_old;//�ĵ�ͼ�����꣨10��130��
	static u16  rate_x=10;                   //�ĵ�ͼ�����꣨10-240��
	/**�����ĵ�ͼ**/		
	rate_y = 158 - (u16)(Signal*Min_Sensor_y);//�ĵ�ͼ������
	if(rate_x<230)
	{
			rate_x++;																 //�ĵ�ͼ�����꣬ÿѭ��һ�λ�һ����
			
			LCD_DrawLine2(rate_x,40,rate_x,175);//�����һ���߶�
	}
	

	
	else rate_x=10;//��ͷ��ʼ��
	
	LCD_DrawLine2(10,0,10,212);//�����һ���߶�
		
	LCD_DrawPoint1(rate_x,rate_y);//�ĵ�ͼ��x���y���Ӧ�ĵ㻭����
	/*�����ڵĵ������ߣ������ֻ�е����*/
	rate_y_buf=rate_y;
	
	LCD_DrawLine1((rate_x-1),rate_y_old,(rate_x-1),rate_y_buf);
  /*�����ĵ�ͼ����������ս��յ��������ź�*/			
	rate_y_old = rate_y;//��¼�˴ε������ź�
}
