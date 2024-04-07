# DAY6

## 模拟量传感器

模拟量传感器可以提供连续的输出信号，通过测量和转换物理量的变化来获取相关信息。其中包括：

#### 光照传感器

光照传感器常用于测量周围环境的光照强度。其特点包括：

- 使用光敏电阻作为传感器元件。
- 光敏电阻的阻值随着光照强度的增加而减小。
- 通过测量电流或电压的变化来确定光照强度的大小。

#### 空气质量传感器

空气质量传感器用于检测周围空气中的污染物浓度，常见的包括二氧化碳、甲醛、颗粒物等。其特点包括：

- 可以测量多种污染物。
- 测量原理多样，通常基于化学反应或光学原理。

![image-20240407191114309](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071911368.png)

对应IO口 **模拟输入**

## ADC（模数转换器）

ADC是模数转换器的简称，它负责将模拟信号转换为数字信号。常见的ADC转换方法之一是逐次逼近法。

### 逐次逼近法

逐次逼近法是一种常见的ADC转换方法，其工作原理如下：

1. **初始化**：首先，ADC将模拟输入信号的范围划分为若干个离散的电平。
2. **比较**：ADC将一个参考电平与输入信号进行比较。
3. **调整**：根据比较结果，ADC调整参考电平，使其更接近输入信号的值。
4. **重复**：反复执行比较和调整步骤，逐渐逼近输入信号的准确值。
5. **完成**：当参考电平与输入信号的差异足够小，ADC将得到一个近似于输入信号的数字输出值。

### 特点

- **高精度**：逐次逼近法可以提供较高的转换精度。
- **适用性**：适用于需要高精度且转换速度较慢的应用场景。
- **复杂度**：相对于其他转换方法，逐次逼近法的硬件和软件复杂度通常较高。

逐次逼近法是ADC中常用的一种转换方法，它通过不断调整参考电平来逼近输入信号的准确值，从而实现模拟信号到数字信号的转换。



查看技术参考手册：

![image-20240407191451442](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071914486.png)

#### ADC特点：

- **数据位数和寄存器对齐**：12位ADC的转换结果会被放置在一个16位的寄存器中，右对齐表示高位填充0。
- **单次和连续转换**：ADC可以进行单次转换，即只进行一次模拟信号到数字信号的转换。也可以进行连续转换，即连续地进行多次转换。
- **扫描和间断模式**：ADC可以工作在扫描模式下，它可以按照事先定义好的顺序依次转换多个通道的模拟信号。间断模式下，ADC只进行单次转换。
- **时钟频率限制**：ADC的时钟频率不能超过14MHz，这个限制保证了转换的准确性和稳定性。
- **通道数量**：ADC具有18个通道，其中16个是外部通道，用于连接外部模拟信号源；另外2个是内部通道，用于测量芯片内部的参考电压等。

![image-20240407191538166](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071915202.png)

## 光照传感器

- 引脚连接：
  - 光照传感器的输出引脚（ILLU）连接到PA5引脚。
- ADC通道：
  - 光照传感器的模拟输出信号通过ADC进行转换。
  - 连接到了ADC1或ADC2的IN5通道。



## 光照传感器和ADC配置步骤

1. **配置PA5引脚为模拟输入模式**：

   ```C
   Copy CodeExplain// 设置PA5引脚为模拟输入模式
   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.Pin = GPIO_PIN_5;
   GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
   ```

2. **配置ADC模式**：

   ```c
   Copy CodeExplainADC_HandleTypeDef hadc;
   // 配置ADC参数
   hadc.Instance = ADC1; // 或者ADC2，根据实际情况选择
   hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
   hadc.Init.Resolution = ADC_RESOLUTION_12B;
   hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
   hadc.Init.ScanConvMode = ADC_SCAN_DISABLE; // 禁用扫描模式
   hadc.Init.ContinuousConvMode = DISABLE; // 选择单次转换模式
   hadc.Init.DiscontinuousConvMode = DISABLE; // 禁用间断模式
   hadc.Init.NbrOfConversion = 1; // 转换通道数量，此处为1
   hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START; // 软件触发转换
   HAL_ADC_Init(&hadc);
   ```

3. **执行ADC自校准**：

   ```C
   Copy Code// 执行ADC自校准
   HAL_ADCEx_Calibration_Start(&hadc);
   ```



### 完整代码：

**adc2.c**

```c
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
u16 mq;
void ADC2_GetValue(void)
{
	//配置ADC通道
	ADC_RegularChannelConfig(ADC2,ADC_Channel_5,1,ADC_SampleTime_55Cycles5);
	
	//开始转换
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);
	while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC) == 0)
	{}
	illu = ADC_GetConversionValue(ADC2);
		printf("illu=%d\r\n",illu);
		//配置ADC通道
	ADC_RegularChannelConfig(ADC2,ADC_Channel_11,1,ADC_SampleTime_55Cycles5);
		//开始转换
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);
		while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC) == 0)
	{}
	mq = ADC_GetConversionValue(ADC2);
		printf("mq=%d\r\n",mq);
}
```

**adc2.h**

```c
#ifndef __ADC2_H
#define __ADC2_H

#include "main.h"

void ADC2_Config();
void ADC2_GetValue();

extern u16 mq;
extern u16 illu;

#endif
```













