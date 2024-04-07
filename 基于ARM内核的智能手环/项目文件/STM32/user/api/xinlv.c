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
		LCD_ShowxNum(20,210,BPM,3,24,0);
		Show_Sensor(Signal);
		printf("Signal=%d\r\n",Signal);
		if (QS == true)
		{		
				LCD_ShowxNum(60,242,BPM,3,16,0);
				
				LCD_ShowxNum(60,262,IBI,3,16,0);
				
				QS = false; // reset the Quantified Self flag for next time
					
				//对BPM值进行范围划分
				
		}
}

void Show_SensorView(void)
{    
	
//	Draw_Text_Str(60,150,BLUE,RED,"* BPM: ");	
//	Draw_Text_Str(60,170,BLUE,RED,"* IBI");	  
}

#define HighY 113               //绘制心电图的最大高度
#define Min_Sensor_y HighY/1024  //绘制心电图的最小精度
void Show_Sensor(u16 signal)
{
	static u16	rate_y,rate_y_buf,rate_y_old;//心电图纵坐标（10—130）
	static u16  rate_x=10;                   //心电图横坐标（10-240）
	/**绘制心电图**/		
	rate_y = 158 - (u16)(Signal*Min_Sensor_y);//心电图纵坐标
	if(rate_x<230)
	{
			rate_x++;																 //心电图横坐标，每循环一次画一个点
			
			LCD_DrawLine2(rate_x,40,rate_x,175);//清除上一次线段
	}
	

	
	else rate_x=10;//从头开始画
	
	LCD_DrawLine2(10,0,10,212);//清除上一次线段
		
	LCD_DrawPoint1(rate_x,rate_y);//心电图中x轴和y轴对应的点画出来
	/*把相邻的点连成线，否则就只有点组成*/
	rate_y_buf=rate_y;
	
	LCD_DrawLine1((rate_x-1),rate_y_old,(rate_x-1),rate_y_buf);
  /*绘制心电图结束，保存刚接收到的心率信号*/			
	rate_y_old = rate_y;//记录此次的心率信号
}
