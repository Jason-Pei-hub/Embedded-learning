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
		LCD_ShowxNum(156,150,BPM,3,16,0);
		Show_Sensor(Signal);
		printf("Signal=%d\r\n",Signal);
		if (QS == true)
		{		
				LCD_ShowxNum(156,150,BPM,3,16,0);
				
				LCD_ShowxNum(156,170,IBI,3,16,0);
				
				QS = false; // reset the Quantified Self flag for next time
					
				//��BPMֵ���з�Χ����
				if(BPM>50&&BPM<100)
					LCD_ShowStringAndHz(60,210,40,16,16,"Good!",0,BLACK);	
				else	
					LCD_ShowStringAndHz(60,210,40,16,16,"Bad! ",0,BLACK);
		}
}

void Show_SensorView(void)
{    
	LCD_ShowStringAndHz(60,150,56,16,16,"* BPM: ",0,BLACK);
	LCD_ShowStringAndHz(60,170,56,16,16,"* IBI",0,BLACK);
//	Draw_Text_Str(60,150,BLUE,RED,"* BPM: ");	
//	Draw_Text_Str(60,170,BLUE,RED,"* IBI");	  
}

#define HighY 120                //�����ĵ�ͼ�����߶�
#define Min_Sensor_y HighY/1024  //�����ĵ�ͼ����С����
void Show_Sensor(u16 signal)
{
	static u16	rate_y,rate_y_buf,rate_y_old;//�ĵ�ͼ�����꣨10��130��
	static u16  rate_x=10;                   //�ĵ�ͼ�����꣨10-240��
	/**�����ĵ�ͼ**/		
	rate_y = 130 - (u16)(Signal*Min_Sensor_y);//�ĵ�ͼ������
	if(rate_x<240)
	{
			rate_x++;																 //�ĵ�ͼ�����꣬ÿѭ��һ�λ�һ����
			POINT_COLOR = WHITE;
			LCD_DrawLine(rate_x,10,rate_x,130,0);//�����һ���߶�
	}
	else rate_x=10;//��ͷ��ʼ��
		
	LCD_DrawPoint(rate_x,rate_y);//�ĵ�ͼ��x���y���Ӧ�ĵ㻭����
	/*�����ڵĵ������ߣ������ֻ�е����*/
	rate_y_buf=rate_y;
	POINT_COLOR = RED;
	LCD_DrawLine((rate_x-1),rate_y_old,(rate_x-1),rate_y_buf,0);
  /*�����ĵ�ͼ����������ս��յ��������ź�*/			
	rate_y_old = rate_y;//��¼�˴ε������ź�
}
