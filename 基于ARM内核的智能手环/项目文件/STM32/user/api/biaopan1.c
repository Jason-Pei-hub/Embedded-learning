#include "biaopan1.h"

void showbiaopan_init()
{
  	
		
  //初始化表盘
	LCD_ShowPicture(0,0,240,320,(u8*)gImage_watch);


}

void showbiaopan(int hour,int min)
{
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

    now_time.tm_min += min;
    now_time.tm_hour += hour;
	
	  //秒针
		get_points_on_concentric_circles(120, 160,0,20,now_time.tm_sec%60+30, &sx3, &sy3, &sx4, &sy4);
		LCD_DrawLine((uint16_t)sx3,(uint16_t)sy3,(uint16_t)sx4,(uint16_t)sy4,0);
    get_points_on_concentric_circles(120, 160,0,117,now_time.tm_sec%60, &sx3, &sy3, &sx4, &sy4);
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

		//清屏
    Delay_ms(900);
		LCD_ShowPicture(0,0,240,320,(u8*)gImage_watch);
		
		now_time.tm_min -= min;
    now_time.tm_hour -= hour;
}