#ifndef _XINLV_H_
#define _XINLV_H_

#include "stm32f10x.h"
#include "main.h"  

extern int IBI;          //���ڽ���ʱ��
extern int BPM;          //����ֵ             
extern int Signal;       //ԭʼ�ź�ֵ            
extern unsigned char QS; //����������־

void Sensor_Init(void);
void sendDataToProcessing(u8 symbol, int16_t dat );
void Show_SensorView(void);
void Sensor(void);
void Show_Sensor(u16 signal);
#endif

