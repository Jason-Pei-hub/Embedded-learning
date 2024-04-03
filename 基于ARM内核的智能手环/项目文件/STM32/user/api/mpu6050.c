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
	//SCL为高电平时，SDA线上数据有效
	MPU_SDA(1);
	Delay_us(4);
	MPU_SCL(1);
	Delay_us(4);
	MPU_SDA(0);
	Delay_us(4);
	MPU_SCL(0)//SCL为低电平为开始发送数据做准备;	
}
void MPU_IIC_Stop(void)
{
	//SCL为高电平时，SDA线上数据有效
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
	 if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7))//SDA输入的电平为高电平表示非应答
  {
    ack = 1;
  }
  else  //SDA输入的电平为低电平表示应答
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
  MPU_SDA(1);//SDA输出高电平，切换为输入
  for(i=0;i<8;i++)  //产生8个时钟，读取8位数据
  {
    Delay_us(10);
    MPU_SCL(1);
    data = data <<1;
    if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7))
    {
      data |= 1<<0;
    }
    else   //SDA输入的低电平电平
    {
      data &=~(1<<0);
    }	
    Delay_us(10);
    MPU_SCL(0);	
  }
  //产生第九个时钟，发送应答信号。
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
函数名:MPU_MPU_IIC_Write
函数的功能：MPU_MPU_IIC写一个字节函数
参数：reg：要写入的寄存器地址 data：要写入寄存器的数据
*/
void MPU_MPU_IIC_Write(u8 reg,u8 data)
{
	MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//发送器件地址+写命令
	MPU_IIC_SendByte(reg);//发送寄存器地址
	MPU_IIC_SendByte(data);//发送数据
	MPU_IIC_Stop();
}
/*函数名:MPU_MPU_IIC_Read_Byte
函数的功能：MPU_MPU_IIC读一个字节函数
参数：reg：要写入的寄存器地址 
返回读取到的数据
*/
u8 MPU_MPU_IIC_Read(u8 reg)	
{
	u8 data;
	MPU_IIC_Start();//0-PA,1-PB
	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//发送器件地址+写命令
	MPU_IIC_SendByte(reg);//发送寄存器地址
	MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|1);//发送器件地址+读命令
	data=MPU_IIC_ReadByte(1);//读取数据,发送nACK
	MPU_IIC_Stop();//0-PA,1-PB
	return data;
}
/*
函数名:MPU_Write_Len
函数的功能：MPU_MPU_IIC连续写入lenth个字节函数
参数：reg：要写入的寄存器地址 buff：要写入的数据地址 lenth：数据长度
*/
void MPU_Write_Len(u8 reg,u8 *buff,u8 lenth)
{
	u8 i=0;
	MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//发送器件地址+写命令
	MPU_IIC_SendByte(reg);//发送寄存器地址
  for(i=0;i<lenth;i++)
  MPU_IIC_SendByte(buff[i]);//连续写入lenth个数据
	MPU_IIC_Stop();
}
/*
函数名:MPU_Read_Len
函数的功能：MPU_MPU_IIC连续读取数据函数
参数：reg：要写入的寄存器地址 buff：读取到的数据存储区 lenth：要读取的数据长度
返回读取到的数据
*/
u8 MPU_Read_Len(u8 reg,u8 *buff,u8 lenth)	
{
	u8 i;
	MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//发送器件地址+写命令
	MPU_IIC_SendByte(reg);//发送寄存器地址
	MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|1);//发送器件地址+读命令
	for(i=lenth;i>0;i--)
	{
		if(i==1)
		{
			buff[lenth-i]=MPU_IIC_ReadByte(1);//读取到最后一位数据,发送nACK
			break;
		}
		else
		buff[lenth-i]=MPU_IIC_ReadByte(0);//开始读取数据,发送ACK
	}
	MPU_IIC_Stop();
	return 0;
}	
/*
函数名:MPU_Set_Gyro_Fsr
函数的功能：设置MPU6050陀螺仪传感器满量程范围
参数：fsr：0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
*/
void MPU_Set_Gyro_Fsr(u8 fsr)
{
  MPU_MPU_IIC_Write(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
}
/*
函数名:MPU_Set_Accel_Fsr
函数的功能：设置MPU6050加速度传感器满量程范围
参数：fsr：0,±2g;1,±4g;2,±8g;3,±16g
*/
void MPU_Set_Accel_Fsr(u8 fsr)
{
  MPU_MPU_IIC_Write(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}
/*
函数名:MPU_Set_LPF
函数的功能：设置MPU6050的数字低通滤波器
参数：lpf：数字低通滤波频率(Hz)
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
  MPU_MPU_IIC_Write(MPU_CFG_REG,data);//设置数字低通滤波器  
}
/*
函数名:MPU_Set_Rate
函数的功能：设置MPU6050的采样率(假定Fs=1KHz)
参数：rate:4~1000(Hz)
*/
void MPU_Set_Rate(u16 rate)
{
  u8 data;
  if(rate>1000)rate=1000;
  if(rate<4)rate=4;
  data=1000/rate-1;
  MPU_MPU_IIC_Write(MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
  MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

/*
函数名:MPU_Get_Gyroscope
函数的功能：得到陀螺仪值(原始值)
参数：gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
返回0 成功  返回其它 失败
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
函数名:MPU_Get_Accelerometer
函数的功能：得到加速度值(原始值)
参数：ax,ay,az:加速度x,y,z轴的原始读数(带符号)
返回0 成功  返回其它 失败
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
//得到温度值
//返回值:温度值(扩大了100倍)
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
函数名:MPU_Init
函数的功能：初始化MPU6050
参数：无
返回0 成功  返回其它 失败
*/  u8 res;
u8 MPU_Init(void)
{
	MPU_GPIO_Config();
  MPU_MPU_IIC_Write(MPU_PWR_MGMT1_REG,0X80);	//复位MPU6050-高位置1
  Delay_ms(300); 
  MPU_MPU_IIC_Write(MPU_PWR_MGMT1_REG,0X00);	//唤醒MPU6050 
  MPU_Set_Gyro_Fsr(3);					//陀螺仪传感器,±2000dps-本设计用于抬腕唤醒
  MPU_Set_Accel_Fsr(0);					//加速度传感器,±2g
  MPU_Set_Rate(50);						//设置采样率50Hz
  MPU_MPU_IIC_Write(MPU_INT_EN_REG,0X00);	//关闭所有中断
  MPU_MPU_IIC_Write(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
  MPU_MPU_IIC_Write(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
  MPU_MPU_IIC_Write(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
  res=MPU_MPU_IIC_Read(MPU_DEVICE_ID_REG);
  printf("res:%x  %d\r\n",res,res);
  if(res==MPU_ADDR)//器件ID正确
  {
    MPU_MPU_IIC_Write(MPU_PWR_MGMT1_REG,0X01);	//设置系统时钟源,PLL X轴为参考
    MPU_MPU_IIC_Write(MPU_PWR_MGMT2_REG,0x00);	//加速度、陀螺仪工作
    MPU_Set_Rate(50);						            //设置采样率为50Hz
		MPU_Set_LPF(20);                        //设置带宽为25HZ
		
		CountStepInit();//步数算法初始化
    return 0;
  }
	else return 1;

}

