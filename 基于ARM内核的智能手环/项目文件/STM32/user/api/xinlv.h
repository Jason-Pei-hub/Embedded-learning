#ifndef _XINLV_H_
#define _XINLV_H_

#include "stm32f10x.h"
#include "main.h"  

extern int IBI;          //相邻节拍时间
extern int BPM;          //心率值             
extern int Signal;       //原始信号值            
extern unsigned char QS; //发现心跳标志

void Sensor_Init(void);
void sendDataToProcessing(u8 symbol, int16_t dat );
void Show_SensorView(void);
void Sensor(void);
void Show_Sensor(u16 signal);
#endif

