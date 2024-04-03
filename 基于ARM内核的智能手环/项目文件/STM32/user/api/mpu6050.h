#ifndef _MPU6050_H_
#define _MPU6050_H_
#include "stm32f10x.h"
#include "delay.h"
#include "main.h"

#define MPU_SCL(x) x ? GPIO_SetBits(GPIOC,GPIO_Pin_6):GPIO_ResetBits(GPIOC,GPIO_Pin_6);
#define MPU_SDA(x) x ? GPIO_SetBits(GPIOC,GPIO_Pin_7):GPIO_ResetBits(GPIOC,GPIO_Pin_7);
#define MPU_SELF_TESTX_REG		0X0D	//自检寄存器X
#define MPU_SELF_TESTY_REG		0X0E	//自检寄存器Y
#define MPU_SELF_TESTZ_REG		0X0F	//自检寄存器Z
#define MPU_SELF_TESTA_REG		0X10	//自检寄存器A
#define MPU_SAMPLE_RATE_REG		0X19	//陀螺仪采样频率分频寄存器
#define MPU_CFG_REG						0X1A	//配置寄存器
#define MPU_GYRO_CFG_REG			0X1B	//陀螺仪配置寄存器
#define MPU_ACCEL_CFG_REG			0X1C	//加速度计配置寄存器
#define MPU_MOTION_DET_REG		0X1F	//运动检测阀值设置寄存器
#define MPU_FIFO_EN_REG				0X23	//FIFO使能寄存器
#define MPU_I2CMST_CTRL_REG		0X24	//MPU_IIC主机控制寄存器
#define MPU_I2CSLV0_ADDR_REG	0X25	//MPU_IIC从机0器件地址寄存器
#define MPU_I2CSLV0_REG				0X26	//MPU_IIC从机0数据地址寄存器
#define MPU_I2CSLV0_CTRL_REG	0X27	//MPU_IIC从机0控制寄存器
#define MPU_I2CSLV1_ADDR_REG	0X28	//MPU_IIC从机1器件地址寄存器
#define MPU_I2CSLV1_REG				0X29	//MPU_IIC从机1数据地址寄存器
#define MPU_I2CSLV1_CTRL_REG	0X2A	//MPU_IIC从机1控制寄存器
#define MPU_I2CSLV2_ADDR_REG	0X2B	//MPU_IIC从机2器件地址寄存器
#define MPU_I2CSLV2_REG				0X2C	//MPU_IIC从机2数据地址寄存器
#define MPU_I2CSLV2_CTRL_REG	0X2D	//MPU_IIC从机2控制寄存器
#define MPU_I2CSLV3_ADDR_REG	0X2E	//MPU_IIC从机3器件地址寄存器
#define MPU_I2CSLV3_REG				0X2F	//MPU_IIC从机3数据地址寄存器
#define MPU_I2CSLV3_CTRL_REG	0X30	//MPU_IIC从机3控制寄存器
#define MPU_I2CSLV4_ADDR_REG	0X31	//MPU_IIC从机4器件地址寄存器
#define MPU_I2CSLV4_REG				0X32	//MPU_IIC从机4数据地址寄存器
#define MPU_I2CSLV4_DO_REG		0X33	//MPU_IIC从机4写数据寄存器
#define MPU_I2CSLV4_CTRL_REG	0X34	//MPU_IIC从机4控制寄存器
#define MPU_I2CSLV4_DI_REG		0X35	//MPU_IIC从机4读数据寄存器

#define MPU_I2CMST_STA_REG		0X36	//MPU_IIC主机状态寄存器
#define MPU_INTBP_CFG_REG			0X37	//中断/旁路设置寄存器
#define MPU_INT_EN_REG				0X38	//中断使能寄存器
#define MPU_INT_STA_REG				0X3A	//中断状态寄存器

#define MPU_ACCEL_XOUTH_REG		0X3B	//加速度值,X轴高8位寄存器
#define MPU_ACCEL_XOUTL_REG		0X3C	//加速度值,X轴低8位寄存器
#define MPU_ACCEL_YOUTH_REG		0X3D	//加速度值,Y轴高8位寄存器
#define MPU_ACCEL_YOUTL_REG		0X3E	//加速度值,Y轴低8位寄存器
#define MPU_ACCEL_ZOUTH_REG		0X3F	//加速度值,Z轴高8位寄存器
#define MPU_ACCEL_ZOUTL_REG		0X40	//加速度值,Z轴低8位寄存器

#define MPU_TEMP_OUTH_REG			0X41	//温度值高八位寄存器
#define MPU_TEMP_OUTL_REG			0X42	//温度值低8位寄存器

#define MPU_GYRO_XOUTH_REG		0X43	//陀螺仪值,X轴高8位寄存器
#define MPU_GYRO_XOUTL_REG		0X44	//陀螺仪值,X轴低8位寄存器
#define MPU_GYRO_YOUTH_REG		0X45	//陀螺仪值,Y轴高8位寄存器
#define MPU_GYRO_YOUTL_REG		0X46	//陀螺仪值,Y轴低8位寄存器
#define MPU_GYRO_ZOUTH_REG		0X47	//陀螺仪值,Z轴高8位寄存器
#define MPU_GYRO_ZOUTL_REG		0X48	//陀螺仪值,Z轴低8位寄存器

#define MPU_I2CSLV0_DO_REG		0X63	//MPU_IIC从机0数据寄存器
#define MPU_I2CSLV1_DO_REG		0X64	//MPU_IIC从机1数据寄存器
#define MPU_I2CSLV2_DO_REG		0X65	//MPU_IIC从机2数据寄存器
#define MPU_I2CSLV3_DO_REG		0X66	//MPU_IIC从机3数据寄存器

#define MPU_I2CMST_DELAY_REG	0X67	//MPU_IIC主机延时管理寄存器
#define MPU_SIGPATH_RST_REG		0X68	//信号通道复位寄存器
#define MPU_MDETECT_CTRL_REG	0X69	//运动检测控制寄存器
#define MPU_USER_CTRL_REG			0X6A	//用户控制寄存器
#define MPU_PWR_MGMT1_REG			0X6B	//电源管理寄存器1
#define MPU_PWR_MGMT2_REG			0X6C	//电源管理寄存器2 
#define MPU_FIFO_CNTH_REG			0X72	//FIFO计数寄存器高八位
#define MPU_FIFO_CNTL_REG			0X73	//FIFO计数寄存器低八位
#define MPU_FIFO_RW_REG				0X74	//FIFO读写寄存器
#define MPU_DEVICE_ID_REG			0X75	//器件ID寄存器
//如果AD0脚(9脚)接地,MPU_IIC地址为0X68(不包含最低位).
//如果接V3.3,则MPU_IIC地址为0X69(不包含最低位).
#define MPU_ADDR				0X68
//重力加速度值，单位：9.5 m/s2
typedef struct 
{
	float accX;
	float accY;
	float accZ;
}accValue_t;
void MPU_MPU_IIC_Write(u8 reg,u8 data);
u8 MPU_MPU_IIC_Read(u8 reg);
short MPU_Get_Temperature(void);
void MPU_Write_Len(u8 reg,u8 *buff,u8 lenth);
u8 MPU_Read_Len(u8 reg,u8 *buff,u8 lenth);
void MPU_Set_Gyro_Fsr(u8 fsr);
void MPU_Set_Accel_Fsr(u8 fsr);
void MPU_Set_LPF(u16 lpf);
void MPU_Set_Rate(u16 rate);
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);
u8 MPU_Init(void);
#endif
