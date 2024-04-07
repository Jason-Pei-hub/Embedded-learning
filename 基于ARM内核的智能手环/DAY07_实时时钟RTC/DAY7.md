# DAY7

## RTC（实时时钟）

### 什么是RTC？

RTC是指实时时钟（Real-Time Clock），是一种能够持续跟踪时间的计时器，即使在设备断电的情况下也能保持时间的准确性。它通常用于需要准确时间记录的应用，比如计时器、日历、数据记录等。

### RTC的工作原理

RTC的核心部分是一个稳定的时钟源，它以一定的频率（比如32.768KHz）运行，并且不会因为设备断电而停止。RTC可以通过内部的计数器来记录经过的时间，从而实现持续跟踪时间的功能。

![image-20240407192522838](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071925884.png)

![image-20240407192529365](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071925404.png)

由于标准库给了，所以我们简单看一下：

## RTC配置和初始化

```
cCopy CodeExplain#include "rtc.h"

// 声明RTC配置和初始化函数
void RTC_Configuration(void);
void Time_Adjust(void);
uint32_t Time_Regulate(void);

// 定义保存当前时间的结构体变量
struct tm now_time;

// RTC配置函数
void RTC_Config(){
    // 检查RTC是否已配置
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        // RTC未配置
        printf("\r\n\n RTC not yet configured....");
        // 进行RTC配置
        RTC_Configuration();
        printf("\r\n RTC configured....");
        // 调整时间
        Time_Adjust();
        // 将配置标志写入备份寄存器
        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
    else
    {
        // RTC已配置
        // 检查复位标志位
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
        {
            printf("\r\n\n Power On Reset occurred....");
        }
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
        {
            printf("\r\n\n External Reset occurred....");
        }
        printf("\r\n No need to configure RTC....");
        // 等待RTC寄存器同步
        RTC_WaitForSynchro();
        // 启用RTC秒中断
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        RTC_WaitForLastTask();
    }
}

// RTC配置函数
void RTC_Configuration(void)
{
    // 启用PWR和BKP时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    // 允许访问BKP域
    PWR_BackupAccessCmd(ENABLE);
    // 复位备份域
    BKP_DeInit();
    // 启用LSE
    RCC_LSEConfig(RCC_LSE_ON);
    // 等待LSE就绪
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {}
    // 选择LSE作为RTC时钟源
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    // 启用RTC时钟
    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForSynchro();
    RTC_WaitForLastTask();
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    RTC_WaitForLastTask();
    RTC_SetPrescaler(32767); // RTC周期 = RTCCLK / RTC_PR = (32.768 KHz) / (32767 + 1)
    RTC_WaitForLastTask();
}

// 获取当前时间的函数
uint32_t Time_Regulate(void)
{
    // 设置当前时间
    now_time.tm_year = 2024-1900;
    now_time.tm_mon = 4-1;
    now_time.tm_mday = 2;
    now_time.tm_hour = 10;
    now_time.tm_min = 13;
    now_time.tm_sec = 0;
    return mktime(&now_time);
}

// 调整时间的函数
void Time_Adjust(void)
{
    RTC_WaitForLastTask();
    RTC_SetCounter(Time_Regulate());
    RTC_WaitForLastTask();
}
```

接着我们通过数学函数画表盘

![image-20240407193013096](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071930125.png)

```c
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
		
		
		u32 time = 0;
 
		
		while(1)
		{
			switch(KEY_Check())
			{
			  case 1:
					showyemian1(HOUR,MIN,CHOUR,CMIN);
				case 2:
					showyemian2();
				case 3:
					showyemian3(TSTEP);
				case 4:
					showyemian4();
					
					
			}
				
				
			BreatheLed();
		  if(dj>=90000)
		{
			
		dj = 0;
    LCD_ShowPicture(0,0,240,320,(u8*)gImage_daiji);
			
		
		time = RTC_GetCounter();
    now_time = *localtime(&time);
		
	  now_time.tm_min += min;
    now_time.tm_hour += hour;
		
			
	  //
		get_points_on_concentric_circles(120, 160,0,20,now_time.tm_sec%60+30, &sx3, &sy3, &sx4, &sy4);
		LCD_DrawLine((uint16_t)sx3,(uint16_t)sy3,(uint16_t)sx4,(uint16_t)sy4,0);
    get_points_on_concentric_circles(120, 160,0,117,now_time.tm_sec%60, &sx3, &sy3, &sx4, &sy4);
		LCD_DrawLine((uint16_t)sx3,(uint16_t)sy3,(uint16_t)sx4,(uint16_t)sy4,0);
		
		//
	  get_points_on_concentric_circles(120, 160,30,115,now_time.tm_min%60, &mx1, &my1, &mx2, &my2);
    get_points_on_concentric_circles(120, 160,7,30,now_time.tm_min%60, &mx3, &my3, &mx4, &my4);

    LCD_DrawLine((uint16_t)mx1,(uint16_t)my1,(uint16_t)mx2,(uint16_t)my2,2);
		LCD_DrawLine((uint16_t)mx3,(uint16_t)my3,(uint16_t)mx4,(uint16_t)my4,0);
		
		//ʱ
	  get_points_on_concentric_circles(120, 160,30,72,now_time.tm_hour%12*5+5*now_time.tm_min/60, &hx1, &hy1, &hx2, &hy2);
    get_points_on_concentric_circles(120, 160,7,30,now_time.tm_hour%12*5+5*now_time.tm_min/60, &hx3, &hy3, &hx4, &hy4);

    LCD_DrawLine((uint16_t)hx1,(uint16_t)hy1,(uint16_t)hx2,(uint16_t)hy2,3);
		LCD_DrawLine((uint16_t)hx3,(uint16_t)hy3,(uint16_t)hx4,(uint16_t)hy4,1);

		
		
		
		}
		}
    
}
```

实现效果:

![46962c1939af2e79ca84a5089ac5bf5](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071935858.jpg)

