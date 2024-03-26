#include "main.h"  

void huxi(int n)
{
	int i = 0;
	int j = 0;
	int m = 0;
	switch(n)
	{
		case 1:
			for(i = 0;i < 1000;i++)
			{
				LED1_ON;
				Delay_us(i);
				LED1_OFF;
				Delay_us(1000-i);
			}
			for(i = 1000;i > 0;i--)
			{
				LED1_ON;
				Delay_us(i);
				LED1_OFF;
				Delay_us(1000-i);
			}
			break;
		case 2:
			for(i = 0;i < 1000;i++)
			{
				LED2_ON;
				Delay_us(i);
				LED2_OFF;
				Delay_us(1000-i);
			}
			for(i = 1000;i > 0;i--)
			{
				LED2_ON;
				Delay_us(i);
				LED2_OFF;
				Delay_us(1000-i);
			}
			break;
			case 3:
			for(i = 0;i < 1000;i++)
			{
				LED3_ON;
				Delay_us(i);
				LED3_OFF;
				Delay_us(1000-i);
			}
			for(i = 1000;i > 0;i--)
			{
				LED3_ON;
				Delay_us(i);
				LED3_OFF;
				Delay_us(1000-i);
			}
			break;
			case 4:
			for(i = 0;i < 1000;i++)
			{
				LED4_ON;
				Delay_us(i);
				LED4_OFF;
				Delay_us(1000-i);
			}
			for(i = 1000;i > 0;i--)
			{
				LED4_ON;
				Delay_us(i);
				LED4_OFF;
				Delay_us(1000-i);
			}
			break;
			case 5:
			for(i = 0;i < 1000;i++)
			{
				LEDR_ON;
				Delay_us(i);
				LEDR_OFF;
				Delay_us(1000-i);
			}
			for(m = 0;m < 1000;m++)
					{
						LEDB_ON;
					  Delay_us(i);
						LEDB_OFF;
				    Delay_us(1000-i);
					}
			for(j = 0;j < 1000;j++)
				{
					LEDG_ON;
					Delay_us(i);
					
					LEDG_OFF;
				  Delay_us(1000-i);
				}
			break;
	}
}
int main(void)
{
	LED_Config();
	RGB_Config();
	KET_Config();
	LEDR_OFF;LEDG_OFF;LEDB_OFF;

	u8 key_flag = 0;
	
	LEDG_ON;
	
	while(1)
	{
//		key_flag = KEY_Check();
//		if(key_flag == 1)
//		{
//			LED2_TURN;
//		}
		huxi(1);
		huxi(2);
		huxi(3);
		huxi(4);
		huxi(5);
		
		
	}
	
}
