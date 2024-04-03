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
	TIM3_Int_Init(1999,71);//定时周期2ms
	Show_SensorView();
//	/* TIM3 重新开时钟，开始计时 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}

/**心率检测*/
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
					
				//对BPM值进行范围划分
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

#define HighY 120                //绘制心电图的最大高度
#define Min_Sensor_y HighY/1024  //绘制心电图的最小精度
void Show_Sensor(u16 signal)
{
	static u16	rate_y,rate_y_buf,rate_y_old;//心电图纵坐标（10—130）
	static u16  rate_x=10;                   //心电图横坐标（10-240）
	/**绘制心电图**/		
	rate_y = 130 - (u16)(Signal*Min_Sensor_y);//心电图纵坐标
	if(rate_x<240)
	{
			rate_x++;																 //心电图横坐标，每循环一次画一个点
			POINT_COLOR = WHITE;
			LCD_DrawLine(rate_x,10,rate_x,130,0);//清除上一次线段
	}
	else rate_x=10;//从头开始画
		
	LCD_DrawPoint(rate_x,rate_y);//心电图中x轴和y轴对应的点画出来
	/*把相邻的点连成线，否则就只有点组成*/
	rate_y_buf=rate_y;
	POINT_COLOR = RED;
	LCD_DrawLine((rate_x-1),rate_y_old,(rate_x-1),rate_y_buf,0);
  /*绘制心电图结束，保存刚接收到的心率信号*/			
	rate_y_old = rate_y;//记录此次的心率信号
}
