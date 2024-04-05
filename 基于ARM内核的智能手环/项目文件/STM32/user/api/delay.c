#include "delay.h"

u32 LED1_TIME;
u8 key_flag_plus;
u32 DHT11_time;
u32 RTC_Time;
u32 XINLV_Time;
u32 MPU6050_Time;
u32 liushui_time;
u32 huxi_time;
u32 on_time;
u32 off_time;
u32 dj;
u32 zy;

//�δ�ʱ�����жϺ���
void SysTick_Handler(void)
{
	LED1_TIME++;
	DHT11_time++;
	RTC_Time++;
	XINLV_Time++;
	MPU6050_Time++;
	on_time++;
	off_time++;
	huxi_time++;
	zy++;
	dj++;
	key_flag_plus = KEY_Check_Plus();
}
	
u8 KEY_Check_Plus(void)
{
  static u32 key_time = 0;
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1)
	{
		key_time++;
		return 0;
	}
	else
	{
		if(key_time >= 1000)
		{
			//������
			key_time = 0;
			return 5;
		}
		else if(key_time <= 500)
		{
			//����̰�
			key_time = 0;
			return 3;
		}
		else
		{
			key_time = 0;
			return 0;
		}
	}
}

void Delay_lus(void)
{
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}

void Delay_us(uint32_t time)
{
	while(time--)
	{
		Delay_lus();
	}
}

void Delay_ms(uint32_t time)
{
	while(time--)
	{
		Delay_us(1000);
	}
}
