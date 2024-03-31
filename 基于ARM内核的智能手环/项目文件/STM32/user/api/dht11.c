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
//dht11_data[0] 湿度高八位
u8 dht11_data[5];

int DHT11_GetVale()
{
	u8 time1 = 0;
  //step1.起始信号
	DHT11_Config(1);
  DHT11_H;
	DHT11_L;
	Delay_ms(20);
	DHT11_H;
	//step2.响应信号
	DHT11_Config(2);
	
	//等待高电平到来
	while(DHT11_R == 1)
	{
		time1++;
		Delay_us(1);
		if(time1 >= 100)
		return 0;
	}
	time1 = 0;
	
	//等待低电平到来
	while(DHT11_R == 0)
	{
		time1++;
		Delay_us(1);
		if(time1 >= 100)
		return 0;
	}
	time1 = 0;
	//step3.接收数据 40位 高位先出
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
  	//判断是1还是0
	  if(DHT11_R == 1)
  	{
	  	//写入1      i 0~39
	  	//              0~4
	  	dht11_data[i/8] |= 0x1<<(7 - i % 8);
			//printf("%d",dht11_data[0/8]);
	  }else if(DHT11_R == 0)
	  {
	  	dht11_data[i/8] &= ~(0x1<<(7 - i % 8));
			//printf("%d",dht11_data[0/8]);
  	}

	}
	//校验
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
