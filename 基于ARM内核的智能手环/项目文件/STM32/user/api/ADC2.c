#include "ADC2.h"

void ADC2_Config()
{
	//PA5 ADC2 IN5
	//����IO�� ģ������
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	

  GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//����ADC2��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	//ʱ����󲻳���14MHZ
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//72/6 12MHZ
	//����ģʽ
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//����ת��
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_InitStruct.ADC_NbrOfChannel = 1;//ת��ͨ����Ŀ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//��ͨ��
	//��ʼ��
	ADC_Init(ADC2,&ADC_InitStruct);
	
	//ʹ��
	ADC_Cmd(ADC2,ENABLE);
	
	//У׼
	//��ֵУ׼��
	ADC_ResetCalibration(ADC2);
	while(ADC_GetResetCalibrationStatus(ADC2) == 1)//�ȴ����óɹ�
	{}
	//��ʼУ׼
	ADC_StartCalibration(ADC2);
	while(ADC_GetCalibrationStatus(ADC2) == 1)//�ȴ�У׼�ɹ�
	{}
}

u16 illu;
void ADC2_GetValue()
{
  //����ADCͨ��
	ADC_RegularChannelConfig(ADC2,ADC_Channel_5,1,ADC_SampleTime_55Cycles5);
  //��ʼת��
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);
	//�ȴ������ɹ�
	while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC) == 0)
	{};
	illu = ADC_GetConversionValue(ADC2);
	printf("%d\r\n",illu);
  //DMA
}
