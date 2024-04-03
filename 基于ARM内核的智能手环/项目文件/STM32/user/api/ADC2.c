#include "ADC2.h"

void ADC2_Config()
{
	//PA5 ADC2 IN5
	//配置IO口 模拟输入
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	

  GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//配置ADC2的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	//时钟最大不超过14MHZ
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//72/6 12MHZ
	//配置模式
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//单次转换
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件启动
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//转换通道数目
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//单通道
	//初始化
	ADC_Init(ADC2,&ADC_InitStruct);
	
	//使能
	ADC_Cmd(ADC2,ENABLE);
	
	//校准
	//充值校准器
	ADC_ResetCalibration(ADC2);
	while(ADC_GetResetCalibrationStatus(ADC2) == 1)//等待重置成功
	{}
	//开始校准
	ADC_StartCalibration(ADC2);
	while(ADC_GetCalibrationStatus(ADC2) == 1)//等待校准成功
	{}
}

u16 illu;
void ADC2_GetValue()
{
  //配置ADC通道
	ADC_RegularChannelConfig(ADC2,ADC_Channel_5,1,ADC_SampleTime_55Cycles5);
  //开始转换
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);
	//等待开启成功
	while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC) == 0)
	{};
	illu = ADC_GetConversionValue(ADC2);
	printf("%d\r\n",illu);
  //DMA
}
