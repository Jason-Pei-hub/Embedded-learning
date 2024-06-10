#include "mpu6050.h"
#include "stdio.h"
#include "StepCount.h"

extern u8 ACK,NACK;
void MPU_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOC, &GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

void MPU_IIC_Start(void)
{
	//SCLΪ�ߵ�ƽʱ��SDA����������Ч
	MPU_SDA(1);
	Delay_us(4);
	MPU_SCL(1);
	Delay_us(4);
	MPU_SDA(0);
	Delay_us(4);
	MPU_SCL(0)//SCLΪ�͵�ƽΪ��ʼ����������׼��;	
}
void MPU_IIC_Stop(void)
{
	//SCLΪ�ߵ�ƽʱ��SDA����������Ч
	MPU_SDA(0);
	Delay_us(4);
	MPU_SCL(1);
	Delay_us(4);
	MPU_SDA(1);
	Delay_us(4);
}
u8 MPU_IIC_SendByte(u8 data)
{
	u8 ack,i;
	for(i=0;i<8;i++)
	{
		if(data&(1<<(7-i)))
		{
			MPU_SDA(1);
		}
		else
			{
				MPU_SDA(0);
		}
			Delay_us(10);
			MPU_SCL(1);
			Delay_us(10);
			MPU_SCL(0);
	}
			MPU_SDA(1);
			Delay_us(10);
    	MPU_SCL(1);
	 if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7))//SDA����ĵ�ƽΪ�ߵ�ƽ��ʾ��Ӧ��
  {
    ack = 1;
  }
  else  //SDA����ĵ�ƽΪ�͵�ƽ��ʾӦ��
  {
    ack = 0;
  }
	Delay_us(10);
	MPU_SCL(0);
	return ack;
}
u8 MPU_IIC_ReadByte(u8 ack)
{
	  u8 i;
  u8 data = 0;
  MPU_SDA(1);//SDA����ߵ�ƽ���л�Ϊ����
  for(i=0;i<8;i++)  //����8��ʱ�ӣ���ȡ8λ����
  {
    Delay_us(10);
    MPU_SCL(1);
    data = data <<1;
    if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7))
    {
      data |= 1<<0;
    }
    else   //SDA����ĵ͵�ƽ��ƽ
    {
      data &=~(1<<0);
    }	
    Delay_us(10);
    MPU_SCL(0);	
  }
  //�����ھŸ�ʱ�ӣ�����Ӧ���źš�
  if(ack == 0)
  {
    MPU_SDA(0);
  }
  else
  {
    MPU_SDA(1);
  }
  Delay_us(10);
  MPU_SCL(1);
  Delay_us(10);
  MPU_SCL(0);
  return data;
}
/*
������:MPU_MPU_IIC_Write
�����Ĺ��ܣ�MPU_MPU_IICдһ���ֽں���
������reg��Ҫд��ļĴ�����ַ data��Ҫд��Ĵ���������
*/
void MPU_MPU_IIC_Write(u8 reg,u8 data)
{
	MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//����������ַ+д����
	MPU_IIC_SendByte(reg);//���ͼĴ�����ַ
	MPU_IIC_SendByte(data);//��������
	MPU_IIC_Stop();
}
/*������:MPU_MPU_IIC_Read_Byte
�����Ĺ��ܣ�MPU_MPU_IIC��һ���ֽں���
������reg��Ҫд��ļĴ�����ַ 
���ض�ȡ��������
*/
u8 MPU_MPU_IIC_Read(u8 reg)	
{
	u8 data;
	MPU_IIC_Start();//0-PA,1-PB
	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//����������ַ+д����
	MPU_IIC_SendByte(reg);//���ͼĴ�����ַ
	MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|1);//����������ַ+������
	data=MPU_IIC_ReadByte(1);//��ȡ����,����nACK
	MPU_IIC_Stop();//0-PA,1-PB
	return data;
}
/*
������:MPU_Write_Len
�����Ĺ��ܣ�MPU_MPU_IIC����д��lenth���ֽں���
������reg��Ҫд��ļĴ�����ַ buff��Ҫд������ݵ�ַ lenth�����ݳ���
*/
void MPU_Write_Len(u8 reg,u8 *buff,u8 lenth)
{
	u8 i=0;
	MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//����������ַ+д����
	MPU_IIC_SendByte(reg);//���ͼĴ�����ַ
  for(i=0;i<lenth;i++)
  MPU_IIC_SendByte(buff[i]);//����д��lenth������
	MPU_IIC_Stop();
}
/*
������:MPU_Read_Len
�����Ĺ��ܣ�MPU_MPU_IIC������ȡ���ݺ���
������reg��Ҫд��ļĴ�����ַ buff����ȡ�������ݴ洢�� lenth��Ҫ��ȡ�����ݳ���
���ض�ȡ��������
*/
u8 MPU_Read_Len(u8 reg,u8 *buff,u8 lenth)	
{
	u8 i;
	MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//����������ַ+д����
	MPU_IIC_SendByte(reg);//���ͼĴ�����ַ
	MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|1);//����������ַ+������
	for(i=lenth;i>0;i--)
	{
		if(i==1)
		{
			buff[lenth-i]=MPU_IIC_ReadByte(1);//��ȡ�����һλ����,����nACK
			break;
		}
		else
		buff[lenth-i]=MPU_IIC_ReadByte(0);//��ʼ��ȡ����,����ACK
	}
	MPU_IIC_Stop();
	return 0;
}	
/*
������:MPU_Set_Gyro_Fsr
�����Ĺ��ܣ�����MPU6050�����Ǵ����������̷�Χ
������fsr��0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
*/
void MPU_Set_Gyro_Fsr(u8 fsr)
{
  MPU_MPU_IIC_Write(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
/*
������:MPU_Set_Accel_Fsr
�����Ĺ��ܣ�����MPU6050���ٶȴ����������̷�Χ
������fsr��0,��2g;1,��4g;2,��8g;3,��16g
*/
void MPU_Set_Accel_Fsr(u8 fsr)
{
  MPU_MPU_IIC_Write(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
/*
������:MPU_Set_LPF
�����Ĺ��ܣ�����MPU6050�����ֵ�ͨ�˲���
������lpf�����ֵ�ͨ�˲�Ƶ��(Hz)
*/
void MPU_Set_LPF(u16 lpf)
{
  u8 data=0;
  if(lpf>=188)data=1;
  else if(lpf>=98)data=2;
  else if(lpf>=42)data=3;
  else if(lpf>=20)data=4;
  else if(lpf>=10)data=5;
  else data=6; 
  MPU_MPU_IIC_Write(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}
/*
������:MPU_Set_Rate
�����Ĺ��ܣ�����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
������rate:4~1000(Hz)
*/
void MPU_Set_Rate(u16 rate)
{
  u8 data;
  if(rate>1000)rate=1000;
  if(rate<4)rate=4;
  data=1000/rate-1;
  MPU_MPU_IIC_Write(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
  MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

/*
������:MPU_Get_Gyroscope
�����Ĺ��ܣ��õ�������ֵ(ԭʼֵ)
������gx,gy,gz:������x,y,z���ԭʼ����(������)
����0 �ɹ�  �������� ʧ��
*/
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
  u8 buff[6],res;  
  res=MPU_Read_Len(MPU_GYRO_XOUTH_REG,buff,6);
  if(res==0)
  {
    *gx=((u16)buff[0]<<8)|buff[1];  
    *gy=((u16)buff[2]<<8)|buff[3];  
    *gz=((u16)buff[4]<<8)|buff[5];
  } 	
  
  return res;;
}
/*
������:MPU_Get_Accelerometer
�����Ĺ��ܣ��õ����ٶ�ֵ(ԭʼֵ)
������ax,ay,az:���ٶ�x,y,z���ԭʼ����(������)
����0 �ɹ�  �������� ʧ��
*/
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
  u8 buff[6],res;  
  res=MPU_Read_Len(MPU_ACCEL_XOUTH_REG,buff,6);
  if(res==0)
  {
    *ax=((u16)buff[0]<<8)|buff[1];  
    *ay=((u16)buff[2]<<8)|buff[3];  
    *az=((u16)buff[4]<<8)|buff[5];
  } 	
  return res;;
}
//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
  short raw;
	float temp;
	MPU_Read_Len(MPU_TEMP_OUTH_REG,buf,2); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;
}
/*
������:MPU_Init
�����Ĺ��ܣ���ʼ��MPU6050
��������
����0 �ɹ�  �������� ʧ��
*/  u8 res;
u8 MPU_Init(void)
{
	MPU_GPIO_Config();
  MPU_MPU_IIC_Write(MPU_PWR_MGMT1_REG,0X80);	//��λMPU6050-��λ��1
  Delay_ms(300); 
  MPU_MPU_IIC_Write(MPU_PWR_MGMT1_REG,0X00);	//����MPU6050 
  MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps-���������̧����
  MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
  MPU_Set_Rate(50);						//���ò�����50Hz
  MPU_MPU_IIC_Write(MPU_INT_EN_REG,0X00);	//�ر������ж�
  MPU_MPU_IIC_Write(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
  MPU_MPU_IIC_Write(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
  MPU_MPU_IIC_Write(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
  res=MPU_MPU_IIC_Read(MPU_DEVICE_ID_REG);
  printf("res:%x  %d\r\n",res,res);
  if(res==MPU_ADDR)//����ID��ȷ
  {
    MPU_MPU_IIC_Write(MPU_PWR_MGMT1_REG,0X01);	//����ϵͳʱ��Դ,PLL X��Ϊ�ο�
    MPU_MPU_IIC_Write(MPU_PWR_MGMT2_REG,0x00);	//���ٶȡ������ǹ���
    MPU_Set_Rate(50);						            //���ò�����Ϊ50Hz
		MPU_Set_LPF(20);                        //���ô���Ϊ25HZ
		
		CountStepInit();//�����㷨��ʼ��
    return 0;
  }
	else return 1;

}

