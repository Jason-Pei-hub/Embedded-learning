#include "dht11.h"


//����ģʽ
void DHT11_Config(u8 i){
	//PG11
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	GPIO_InitTypeDef GPIO_InitStrcut;
	GPIO_InitStrcut.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStrcut.GPIO_Speed=GPIO_Speed_50MHz;
	if(i==1)
		GPIO_InitStrcut.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	else if(i==2)
		GPIO_InitStrcut.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOG,&GPIO_InitStrcut);
}

DHT11 dht11;


u8 dht11_data[5];
//��ȡ��ʪ��
int DHT11_GetValue(void){
	//1.��ʼ�ź�
	DHT11_Config(1);//���ģʽ
//	GPIO_WriteBit(GPIOG,GPIO_Pin_11,Bit_SET);//�ߵ�λ
	DHT11_H;
	DHT11_L;
	Delay_ms(20);
	DHT11_H;
	u8 time1;
	//2.��Ӧ�ź�
	GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11);//������
	DHT11_Config(2);//�л�Ϊ����ģʽ
	//�ȴ��͵�ƽ�ĵ���
	while(DHT11_R==1){
	
		time1++;
		Delay_us(1);
		if(time1>=100)
		{
			return 0;
		
		}
		}
		time1=0;
	//�ȴ��ߵ�ƽ�ĵ���
	while(DHT11_R==0){
	
		time1++;
		Delay_us(1);
		if(time1>=100)
		{
			return 0;
		
		}
		}
		time1=0;
	//��������
	for(int i=0;i<40;i++){
	
	//�ȴ��͵�ƽ�ĵ���
	while(DHT11_R==1){
	
		time1++;
		Delay_us(1);
		if(time1>=100)
		{
			return 0;
		
		}
		}
		time1=0;
		
	//�ȴ��ߵ�ƽ�ĵ���
	while(DHT11_R==0){
	
		time1++;
		Delay_us(1);
		if(time1>=100)
		{
			return 0;
		
		}
		}
		time1=0;
	
		Delay_us(30);
		
		if(DHT11_R==1)//0-39 8 0-7 0 8-15 1
		{
			dht11_data[i/8] |= 0x1 << (7-i%8);
			
		}
		else if(DHT11_R==0){
			dht11_data[i/8]&=~(0x1<<(7-i%8));
		
		
		
		
		}
	
	
	}
	//У��
	if(dht11_data[4]==dht11_data[0]+dht11_data[1]+dht11_data[2]+dht11_data[3]){
		dht11.hum = dht11_data[0];
		dht11.tem = dht11_data[2]+dht11_data[3]/10.0;
		return 2;
	}
	else 
	{
		return 1;
	}
//	return 0;
}


