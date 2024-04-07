
#ifndef _StepCount_H_
#define _StepCount_H_
#include "stm32f10x.h"
typedef signed short      DATATYPE;
#define DATASIZE    30
typedef struct __DATA {
    DATATYPE Data[DATASIZE];
    DATATYPE Max;
    DATATYPE MaxMark;
    DATATYPE Min;
    DATATYPE MinMark;
    DATATYPE Base;
    DATATYPE UpLimit;
    DATATYPE DownLimit;
}__DATA;

typedef struct _SensorData {
    __DATA X;
    __DATA Y;
    __DATA Z;
}SensorData;

extern unsigned short StepCount;
extern short ax,ay,az;


void DataInit(SensorData *SData);
unsigned char DataSelect(SensorData *GMeter);
void CountStepInit(void);
u16 CountStep(signed short X,signed short Y,signed short Z);
void UartSendPacket(unsigned char *ucData, unsigned char ucSize);

#endif
