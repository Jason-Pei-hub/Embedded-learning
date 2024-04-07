//��ֹͷ�ļ��ظ�չ��
#ifndef __MAIN_H
#define __MAIN_H
#define BreatheMax 280

#include "stm32f10x.h"   
#include "led.h"
#include "delay.h"
#include "key.h"
#include <stdio.h>
#include "beep.h"
#include "usart1.h"
#include <string.h>
#include "bsp_lcd.h"
#include "dht11.h"
#include "ADC2.h"
#include <math.h>
#include "draw.h"
#include <time.h>
#include "rtc.h"
#include "xinlv.h"
#include "biaopan1.h"
#include "mpu6050.h"
#include "StepCount.h"
#include "daiji1.h"  

//extern const unsigned char gImage_daiji[153600];
extern const unsigned char gImage_zhuye[153600];
extern const unsigned char gImage_ymxl[2048] ;
extern const unsigned char gImage_ymyd[23520];
extern const unsigned char gImage_ymwd[153600];


void BreatheLed(void);

#endif
