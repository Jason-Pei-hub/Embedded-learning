#ifndef __RTC_H
#define __RTC_H

#include "main.h"


void RTC_Configuration(void);
void Time_Adjust(void);
extern struct tm now_time;

#endif

