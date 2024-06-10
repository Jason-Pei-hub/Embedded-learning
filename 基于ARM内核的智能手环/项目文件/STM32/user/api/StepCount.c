
#include "StepCount.h"

SensorData GMeter;
unsigned short StepCount1 = 0;

unsigned short m = 0;
unsigned char n = 0;
DATATYPE DateBufferX[10] = {9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000};
DATATYPE DateBufferY[10] = {9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000};
DATATYPE DateBufferZ[10] = {9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000};
unsigned short StepCount = 0;
unsigned char StepFlag  = 0;
unsigned char InitFlag = 0;
unsigned char m_count = 0;
unsigned char GMeterAmax = 0;

short ax,ay,az; //计步(加速度值)


void DataInit(SensorData *SData)
{
    SData->X.Max = -8192;
    SData->X.Min = +8192;
    SData->Y.Max = -8192;
    SData->Y.Min = +8192;
    SData->Z.Max = -8192;
    SData->Z.Min = +8192;
}

//找出以哪个方向为记步的标准轴（人走路时，抬起和放下，垂直于地面上的加速度值变化最大）
unsigned char DataSelect(SensorData *GMeter)
{
    DATATYPE tempX = 0, tempY = 0, tempZ = 0, tempMax;
    unsigned char flag = 0;
    tempX = GMeter->X.Max - GMeter->X.Min;
    tempY = GMeter->Y.Max - GMeter->Y.Min;
    tempZ = GMeter->Z.Max - GMeter->Z.Min;
    if(tempX > tempY) {
        if(tempX > tempZ) {
            flag = 1;
            tempMax = tempX;
        } else {
            flag = 3;
            tempMax = tempZ;
        }
    } else {
        if(tempY > tempZ) {
            flag = 2;
            tempMax = tempY;
        } else {
            flag = 3;
            tempMax = tempZ;
        }
    }
    if(tempMax > 1000) {
        return flag;
    } else {
        return 0;
    }
}
/*********************************************************************************************************
** Function name:           main
** Descriptions:            计步
**                          现象：记录人走路或跑步时的步数，并将数据打包通过串口和无线模块发送出去
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              smallmount
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
void CountStepInit(void)
{
    DataInit(&GMeter);
}
/*********************************************************************************************************
** Function name:           main
** Descriptions:            计步
**                          现象：记录人走路或跑步时的步数，并将数据打包通过串口和无线模块发送出去
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              smallmount
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/

u16 CountStep(signed short X,signed short Y,signed short Z)
{
	unsigned char i=0;
  //printf("开始步数:%d\r\n",StepCount);
 /*********************************************************///求出 X Y Z方向上的加速度值                            
   X = X / 4;                                                 //为什么除于4？？？
   Y = Y / 4;
   Z = Z / 4;
   if(m == DATASIZE)   //当检测到30次后？
   {
      m = 0;
      if(m_count == 0) {
         m_count = 1;
      }
    }
    if(n == 10) n = 0; //保存数据n次  当10次后，从新保存
    DateBufferX[n] = X;
    DateBufferY[n] = Y;
    DateBufferZ[n] = Z;
    if(InitFlag < 9) 
	{
         GMeter.X.Data[m] = X;
         GMeter.Y.Data[m] = Y;
         GMeter.Z.Data[m] = Z;
         InitFlag++;
     } 
	 else 
	 {
         GMeter.X.Data[m] = (DateBufferX[0] + DateBufferX[1] + DateBufferX[2] + DateBufferX[3] + DateBufferX[4] + DateBufferX[5] + DateBufferX[6] + DateBufferX[7] + DateBufferX[8] + DateBufferX[9]) / 10;
         GMeter.Y.Data[m] = (DateBufferY[0] + DateBufferY[1] + DateBufferY[2] + DateBufferY[3] + DateBufferY[4] + DateBufferY[5] + DateBufferY[6] + DateBufferY[7] + DateBufferY[8] + DateBufferY[9]) / 10;
         GMeter.Z.Data[m] = (DateBufferZ[0] + DateBufferZ[1] + DateBufferZ[2] + DateBufferZ[3] + DateBufferZ[4] + DateBufferZ[5] + DateBufferZ[6] + DateBufferZ[7] + DateBufferZ[8] + DateBufferZ[9]) / 10;
     }
	 if(m_count == 1)
	 {
            if(GMeter.X.MaxMark == m || GMeter.X.MinMark == m || GMeter.Y.MaxMark == m || GMeter.Y.MinMark == m || GMeter.Z.MaxMark == m || GMeter.Z.MinMark == m) 
			{
                unsigned char tempXMaxMark = GMeter.X.MaxMark;
                unsigned char tempXMinMark = GMeter.X.MinMark;
                unsigned char tempYMaxMark = GMeter.Y.MaxMark;
                unsigned char tempYMinMark = GMeter.Y.MinMark;
                unsigned char tempZMaxMark = GMeter.Z.MaxMark;
                unsigned char tempZMinMark = GMeter.Z.MinMark;
                if(GMeter.X.MaxMark == m) {
                    GMeter.X.Max = -8192;
                }
                if(GMeter.X.MinMark == m) {
                    GMeter.X.Min = +8192;
                }
                if(GMeter.Y.MaxMark == m) {
                    GMeter.Y.Max = -8192;
                }
                if(GMeter.Y.MinMark == m) {
                    GMeter.Y.Min = +8192;
                }
                if(GMeter.Z.MaxMark == m) {
                    GMeter.Z.Max = -8192;
                }
                if(GMeter.Z.MinMark == m) {
                    GMeter.Z.Min = +8192;
                }
                for(i = 0; i < DATASIZE; i++) {
                    if(GMeter.X.MaxMark == m) {
                        if(GMeter.X.Data[i] >= GMeter.X.Max) {
                            GMeter.X.Max = GMeter.X.Data[i];
                            tempXMaxMark = i;
                        }
                    }
                    if(GMeter.X.MinMark == m) {
                        if(GMeter.X.Data[i] <= GMeter.X.Min) {
                            GMeter.X.Min = GMeter.X.Data[i];
                            tempXMinMark = i;
                        }
                    }
                    if(GMeter.Y.MaxMark == m) {
                        if(GMeter.Y.Data[i] >= GMeter.Y.Max) {
                            GMeter.Y.Max = GMeter.Y.Data[i];
                            tempYMaxMark = i;
                        }
                    }
                    if(GMeter.Y.MinMark == m) {
                        if(GMeter.Y.Data[i] <= GMeter.Y.Min) {
                            GMeter.Y.Min = GMeter.Y.Data[i];
                            tempYMinMark = i;
                        }
                    }
                    if(GMeter.Z.MaxMark == m) {
                        if(GMeter.Z.Data[i] >= GMeter.Z.Max) {
                            GMeter.Z.Max = GMeter.Z.Data[i];
                            tempZMaxMark = i;
                        }
                    }
                    if(GMeter.Z.MinMark == m) {
                        if(GMeter.Z.Data[i] <= GMeter.Z.Min) {
                            GMeter.Z.Min = GMeter.Z.Data[i];
                            tempZMinMark = i;
                        }
                    }
                }
                GMeter.X.MaxMark = tempXMaxMark;
                GMeter.X.MinMark = tempXMinMark;
                GMeter.Y.MaxMark = tempYMaxMark;
                GMeter.Y.MinMark = tempYMinMark;
                GMeter.Z.MaxMark = tempZMaxMark;
                GMeter.Z.MinMark = tempZMinMark;
            }
     }
     if(GMeter.X.Data[m] >= GMeter.X.Max) 
	 {
            GMeter.X.Max = GMeter.X.Data[m];
            GMeter.X.MaxMark = m;
     }
     if(GMeter.X.Data[m] <= GMeter.X.Min) 
	 {
            GMeter.X.Min = GMeter.X.Data[m];
            GMeter.X.MaxMark = m;
     }
     if(GMeter.Y.Data[m] >= GMeter.Y.Max)
	 {
            GMeter.Y.Max = GMeter.Y.Data[m];
            GMeter.Y.MaxMark = m;
     }
     if(GMeter.Y.Data[m] <= GMeter.Y.Min) 
	 {
            GMeter.Y.Min = GMeter.Y.Data[m];
            GMeter.Y.MinMark = m;
     }
     if(GMeter.Z.Data[m] >= GMeter.Z.Max) 
	 {
            GMeter.Z.Max = GMeter.Z.Data[m];
            GMeter.Z.MaxMark = m;
     }
     if(GMeter.Z.Data[m] <= GMeter.Z.Min) 
	 {
            GMeter.Z.Min = GMeter.Z.Data[m];
            GMeter.Z.MinMark = m;
     }
        GMeter.X.Base      = (GMeter.X.Max + GMeter.X.Min) / 2;
        GMeter.Y.Base      = (GMeter.Y.Max + GMeter.Y.Min) / 2;
        GMeter.Z.Base      = (GMeter.Z.Max + GMeter.Z.Min) / 2;
        GMeter.X.UpLimit   = (GMeter.X.Base + GMeter.X.Max * 2) / 3;
        GMeter.Y.UpLimit   = (GMeter.Y.Base + GMeter.Y.Max * 2) / 3;
        GMeter.Z.UpLimit   = (GMeter.Z.Base + GMeter.Z.Max * 2) / 3;
        GMeter.X.DownLimit = (GMeter.X.Base + GMeter.X.Min * 2) / 3;
        GMeter.Y.DownLimit = (GMeter.Y.Base + GMeter.Y.Min * 2) / 3;
        GMeter.Z.DownLimit = (GMeter.Z.Base + GMeter.Z.Min * 2) / 3;
        GMeterAmax = DataSelect(&GMeter);
        switch(GMeterAmax) 
		{
            case 1:
            if((GMeter.X.Data[m] > GMeter.X.UpLimit) && StepFlag == 0) StepFlag = 1;
            if((GMeter.X.Data[m] < GMeter.X.DownLimit) && StepFlag ==1) 
			{
                StepFlag = 0;
                StepCount++;
            }
            break;
        case 2:
            if((GMeter.Y.Data[m] > GMeter.Y.UpLimit) && StepFlag == 0) {
                StepFlag = 1;
            }
            if((GMeter.Y.Data[m] < GMeter.Y.DownLimit) && StepFlag ==1) {
                StepFlag = 0;
                StepCount++;
            }
            break;
        case 3:
            if((GMeter.Z.Data[m] > GMeter.Z.UpLimit) && StepFlag == 0) {
                StepFlag = 1;
            }
            if((GMeter.Z.Data[m] < GMeter.Z.DownLimit) && StepFlag ==1) {
                StepFlag = 0;
                StepCount++;
            }
            break;
        default:  break;
        }
        m++;
        n++;
        
        //printf("结束步数:%d\r\n",StepCount);
        StepCount1 = StepCount;
        //printf("结束步数:%d\r\n",StepCount1);
		    return StepCount;
}


