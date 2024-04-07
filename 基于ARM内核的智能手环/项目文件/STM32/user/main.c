#include "main.h"  

#define BreatheMax 280
#define HOUR 16
#define MIN 50
#define CHOUR 17
#define CMIN 50
#define TSTEP 100

void BreatheLed(void)
{
    static int *p = NULL; // ����Ϊstatic����������ʼ��ΪNULL
    static unsigned char B_Reverse= 0;
    static int Low_Time = 0;
    static int tem = 0;
    static unsigned char isCycleComplete = 0; // ���ٵƵ������Ƿ����

    // ��ʼ�� LED Ϊ�ر�״̬
    LED1_OFF;
    LED2_OFF;
    LED3_OFF;
    LED4_OFF;

    // ���pΪNULL������ָ��һ��ȫ�ֱ������Ա��ں�������֮�䱣����ֵ
    if (p == NULL) {
        static int global_p = 0; // ȫ�ֱ������ڱ���p��ֵ
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

                // ��ǰ�Ƶ��������
                isCycleComplete = 1;
            }
        }   
    }

    // ����LED�ĺ���Ч��
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

    // ����p��ֵ
    if (isCycleComplete) {
        *p = (*p + 1) % 6; // �л�����һ����
        isCycleComplete = 0; // �����������״̬
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
	
	MPU_Init();//����ģ���ʼ��
	CountStepInit();//�Ʋ�������ʼ��


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
