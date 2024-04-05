#include "daiji1.h"  

void DaiJi()
{
	int r = 0;
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	
	
	LCD_Clear(0X00);	
	
	for(r = 0; r <142;r++)
	{
	  LCD_Draw_Circle(120,160,r,0xFC89);
		Delay_us(4000-r*20);
	}

	for(r = 0; r <135;r++)                                      
	{
	  LCD_Draw_Circle(120,160,r,0X0000);
		Delay_us(4000-r*20);
	}
	
	for(r = 1;r<=12;r++)
	{
	  get_points_on_concentric_circles(120, 160,100,115,r*5-5, &x1, &y1, &x2, &y2);
	  LCD_DrawLine((uint16_t)x1,(uint16_t)y1,(uint16_t)x2,(uint16_t)y2,2);
		Delay_ms(100);
	}

  for(r = 0; r <6;r++)
	{
	  LCD_Draw_Circle(120,160,r,0xFFFF);
		Delay_ms(100);
	}
	
	for(r = 0; r <5;r++)
	{
	  LCD_Draw_Circle(120,160,r,0x0000);
		Delay_ms(100);
	}


}