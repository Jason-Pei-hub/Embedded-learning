#include "main.h"  

int main(void)
{
	LED_Config();
	RGB_Config();
	KET_Config();
	BEEP_Config();
	SysTick_Config(72000);
	USART1_Config(115200);
	LEDR_OFF;LEDG_OFF;LEDB_OFF;
  u8 key_flag = 0;
	char arr[20] = "hello world!\r\n";
	
	while(1)
	{
		//任务1 状态指示灯
		if(LED1_TIME >= 500)
		{
			LED1_TURN;
			LED1_TIME = 0;
			USART1_SendStr(arr);
		}
		
		//任务2
//		key_flag = KEY_Check();
//		if(key_flag == 1)
//		{
//			LED2_TURN;
//		}
		
//		if(key_flag_plus == 3)
//		{
//			key_flag_plus = 0;
//			LED2_TURN;
//		}
//		else if(key_flag_plus == 5)
//		{
//			key_flag_plus = 0;
//			LEDR_TURN;
//		}
//		BEEP_OFF;
//		Delay_ms(500);
	}
	
}
