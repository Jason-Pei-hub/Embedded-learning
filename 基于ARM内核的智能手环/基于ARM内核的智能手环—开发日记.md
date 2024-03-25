# 基于ARM内核的智能手环

---

> 整体介绍



## 背景

**项目名称：智能手环** 

**项目背景：** 智能手环诞生之初是为了能够记录人们的运动情况，监测用户的健康状况，以期培养健康而科学的运动和生活习惯。随着产品的优化和升级，智能手环的监测功能逐步延伸到能够对用户的活动、锻炼、心率监控等进行持续性地监测和反馈。

![image-20240325214928343](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403252149488.png)

## 项目架构

智能手环由 ARM 内核 MCU(Cortex-M 系列)、TFTLCD 屏、温湿度传感器、心率传感器、

加速度传感器等主要几部分构成。该平台硬件采用 STM32 芯片，通过对温湿度传感器的驱动编写，获取周围温湿度数据，并在 LCD 屏显示，通过对心率传感器对人体心率的采集，获取实时心率值，并在 LCD 屏绘制心率曲线图以及心率值，通过对加速度传感器对人体运动数据进行采集，结合计步算法，计算出人所走的步数，并在 LCD 屏显示，同时可以通过 RTC 记录当前时间，并在 LCD 屏显示时间以及电子数字时钟。



## 需要实现的功能

GPIO口点灯、按键检测、非阻塞轮询、串口通信、LCD、温湿度传感器、ADC、RTC、心率传感器、加速度传感器



## 产品开发流程

1. **项目是怎么来的？**

   * 竞品调研

   * 市场调研

2. **产品的立项（项目经理/老板）**

3. **项目的研发**

   硬件研发：原理板的绘制、PCB板、焊接

   软件研发：配合硬件工程师实现对应的功能

4. **产品的测试**

   硬件测试：产品使用次数上限、零部件的损耗速率

   软件测试：修改BUG

5. **产品的售后服务**

   产品的升级和BUG的修复



## 嵌入式

**什么是嵌入式？**

> 嵌入式系统，从客户需求出发，**灵活裁剪**软硬件的**现代计算机技术**



**嵌入式应用领域**

![image-20240325215037202](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403252150330.png)

![image-20240325094352905](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403250943947.png)

### MCU

微型控制单元

单片机

微型计算机

![image-20240325215046965](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403252150034.png)

### 单片机的厂商

ST意法半导体			NXP恩智浦				德州仪器



兆易创新GD32      	乐鑫科技ESP32		



### STM32

> 内存更大，接口更丰富，市场占有量大

ST 意法半导体

M  ARM公司  M3

32位



### STM32内部结构

查手册

![image-20240325215101114](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403252151219.png)

### 环境搭建

编写代码：用C语言写代码

编译代码：编译成可执行代码

![image-20240325110137822](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403251101895.png)

见pdf

## 项目源码

![image-20240325145709519](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403251457556.png)

> lib 				 库
>
> project 		自动创建
>
> startup  	   项目启动文件
>
> user			  用户—main.c，main.h
>
> api				 接口文件





## 芯片类型

STM32F103ZET6



## 项目开发的三种方式

1. 寄存器：位操作
2. 标准库、固件库：技术成熟（已经不再更新）
3. HAL库：图形化开发



## LED灯与GPIO口

led灯能干啥？

状态指示灯

> 看原理图，找到对应的引脚

![image-20240325160714163](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403251607284.png)

绿色LED1叫网络标号

网络标号：相同的网络标号是练习在一起的

![image-20240325161218173](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403251612241.png)

### GPIO口命名规则：



**通用输入输出的规则**



P：port（端口）

E：A B C....端口号

2：0~15 （16）端口位



GPIO口的模式：

![image-20240325161732220](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403251617252.png)

![image-20240325161900451](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403251619507.png)

IO口在最右边

VDD是内部电源：3.3V

锯齿状：电阻

开关闭合，内部接电源，上拉

> 机器只能识别0和1
>
> 电压值：模拟量
>
> 数字量：0    1
>
> 所以我们规定
>
> 0：0V
>
> 1：2.5-5V

VSS：内部地

开关闭合为下拉

如果没有上拉和下拉，就是浮空数



![image-20240325163056792](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403251630829.png)

两个输出源

如果从输出数据寄存器输出，叫通用输出

片上外设：复用输出

推挽可以输出输出

开漏只能输出0

* 输入模式：

  1. 上拉输入：默认输入高电平

  2. 下拉输入：默认输入低电平

  3. 浮空输入：没有上下拉
  4. 模拟输入：ADC

* 输出模式：

  1. 推挽输出：0 1
  2. 开漏输出：不能通过自身输出高电平信号
  3. 复用推挽
  4. 复用开漏

  

所以我们控制led灯所用的是输出模式中的推挽输出

PE2 输出 0  灯开

输出1          灯关



### 找到对应的IO口

LED1 —— PE2

LED2 —— PE3



### 3.配置IO口模式

PE2		推挽输出



### 写代码

![image-20240325165241423](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403251652451.png)

```c
#include "main.h"  

int main(void)
{
	//LED1 PE2 推挽输出
	//配置IO口步骤
	//step1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	//step2.配置IO口模式
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.初始化IO口
	GPIO_Init(GPIOE,&GPIO_InitSTRUCT);
	
	//PE2输出低电平
	GPIO_WriteBit(GPIOE,GPIO_Pin_2,Bit_RESET);
	while(1)
	{
		
	}
}
```

