#include "dht11.h"
  


void DHT11_Config(u8 i)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = (i == 1 ? GPIO_Mode_Out_PP:GPIO_Mode_IN_FLOATING);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	

	GPIO_Init(GPIOG,&GPIO_InitStruct);
}

DHT11 dht11;
//dht11_data[0] ʪ�ȸ߰�λ
u8 dht11_data[5];

int DHT11_GetVale()
{
	u8 time1 = 0;
  //step1.��ʼ�ź�
	DHT11_Config(1);
  DHT11_H;
	DHT11_L;
	Delay_ms(20);
	DHT11_H;
	//step2.��Ӧ�ź�
	DHT11_Config(2);
	
	//�ȴ��ߵ�ƽ����
	while(DHT11_R == 1)
	{
		time1++;
		Delay_us(1);
		if(time1 >= 100)
		return 0;
	}
	time1 = 0;
	
	//�ȴ��͵�ƽ����
	while(DHT11_R == 0)
	{
		time1++;
		Delay_us(1);
		if(time1 >= 100)
		return 0;
	}
	time1 = 0;
	//step3.�������� 40λ ��λ�ȳ�
	int i = 0;
	for(i = 0;i < 40;i++)
	{
		while(DHT11_R == 1)
	  {
		  time1++;
		  Delay_us(1);
	  	if(time1 >= 100)
	  	return 0;
  	}
	  time1 = 0;
	  
		while(DHT11_R == 0)
	  {
		  time1++;
		  Delay_us(1);
	  	if(time1 >= 100)
	  	return 0;
  	}
	  time1 = 0;
		
	  Delay_us(30);
  	//�ж���1����0
	  if(DHT11_R == 1)
  	{
	  	//д��1      i 0~39
	  	//              0~4
	  	dht11_data[i/8] |= 0x1<<(7 - i % 8);
			//printf("%d",dht11_data[0/8]);
	  }else if(DHT11_R == 0)
	  {
	  	dht11_data[i/8] &= ~(0x1<<(7 - i % 8));
			//printf("%d",dht11_data[0/8]);
  	}

	}
	//У��
	if(dht11_data[4] == dht11_data[0] + dht11_data[1] + dht11_data[2] + dht11_data[3])//
	{
		printf("****************\r\n");
	  dht11.hum = dht11_data[0];
		dht11.tem = dht11_data[2] + dht11_data[3] / 10.0;
    printf("hum = %d\r\ntem = %d\r\n",dht11_data[0],dht11_data[2] + dht11_data[3] / 10.0);
		printf("*****verify*****\r\n");
		printf("****************\r\n");
		return 2;
	}else
	{
	  return 1;
	}
}
