#include "main.h"  

#define BreatheMax 280
#define HOUR 16
#define MIN 50
#define CHOUR 17
#define CMIN 50
#define TSTEP 100

void BreatheLed(void)
{
    static int *p = NULL; // 声明为static变量，并初始化为NULL
    static unsigned char B_Reverse= 0;
    static int Low_Time = 0;
    static int tem = 0;
    static unsigned char isCycleComplete = 0; // 跟踪灯的周期是否完成

    // 初始化 LED 为关闭状态
    LED1_OFF;
    LED2_OFF;
    LED3_OFF;
    LED4_OFF;

    // 如果p为NULL，则将其指向一个全局变量，以便在函数调用之间保持其值
    if (p == NULL) {
        static int global_p = 0; // 全局变量用于保存p的值
        p = &global_p;
    }

    if (!B_Reverse)   
    {
        tem++;                  
        if (tem > BreatheMax)
        {
            tem = 0;
            Low_Time++;             
            if (Low_Time >= BreatheMax) 
            {
                B_Reverse = 1;   
            }
        }   
    }
    else        
    {
        tem++;
        if (tem > BreatheMax)
        {
            tem = 0;
            Low_Time--;         
            if (Low_Time < 0) 
            {
                B_Reverse = 0;

                // 当前灯的周期完成
                isCycleComplete = 1;
            }
        }   
    }

    // 控制LED的呼吸效果
    switch (*p)
    {
        case 0:
            (tem > BreatheMax - Low_Time) ? LED1_OFF : LED1_ON; 
            break;
        case 1:
            (tem > BreatheMax - Low_Time) ? LED2_OFF : LED2_ON; 
            break;
        case 2:
            (tem > BreatheMax - Low_Time) ? LED3_OFF : LED3_ON; 
            break;
        case 3:
            (tem > BreatheMax - Low_Time) ? LED4_OFF : LED4_ON; 
            break;
        case 4:
            (tem > BreatheMax - Low_Time) ? LED3_OFF : LED3_ON; 
            break;
        case 5:
            (tem > BreatheMax - Low_Time) ? LED2_OFF : LED2_ON; 
            break;
        default:
            break;
    }

    // 更新p的值
    if (isCycleComplete) {
        *p = (*p + 1) % 6; // 切换到下一个灯
        isCycleComplete = 0; // 重置周期完成状态
    }
}




int main(void)
{

	
	LED_Config();
	
	KEY_Config();
	BEEP_Config();
  TFTLCD_Init();
	ADC2_Config();
	RTC_Configuration();
  USART1_Config(115200);
	
	MPU_Init();//心率模块初始化
	CountStepInit();//计步函数初始化


	SysTick_Config(72000);
	
	Sensor_Init();
	
//	u8 buf[24] = {0};



 
	
	DaiJi();

	while(1)
	{
		
		
		BreatheLed();

		showbiaopan(HOUR,MIN);
	
	}
	
}
