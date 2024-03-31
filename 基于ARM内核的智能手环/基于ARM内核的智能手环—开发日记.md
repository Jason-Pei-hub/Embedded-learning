# 基于ARM内核的智能手环

---

> 整体介绍
>
> 智能手环由 ARM 内核 MCU(Cortex-M 系列)、TFTLCD 屏、温湿度传感器、心率传感器、
>
> 加速度传感器等主要几部分构成。该平台硬件采用 STM32 芯片，通过对温湿度传感器的驱动编写，获取周围温湿度数据，并在 LCD 屏显示，通过对心率传感器对人体心率的采集，获取实时心率值，并在 LCD 屏绘制心率曲线图以及心率值，通过对加速度传感器对人体运动数据进行采集，结合计步算法，计算出人所走的步数，并在 LCD 屏显示，同时可以通过 RTC 记录当前时间，并在 LCD 屏显示时间以及电子数字时钟。





# DAY1

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

然后输出高低电平即可控制灯的亮灭

```c\
GPIO_WriteBit(GPIOE,GPIO_Pin_2,Bit_SET);
```



那么每次都这样写是不是有点点麻烦

所以我们宏定义一下



```c
#define LED1_ON GPIO_WriteBit(GPIOE,GPIO_Pin_2,Bit_RESET)
#define LED1_OFF GPIO_WriteBit(GPIOE,GPIO_Pin_2,Bit_SET)
```



这样我们就可以轻松的控制小灯的亮灭了

# DAY2

> 本次重点
>
> * STM32寄存器来控制led灯状态反转
>
> * 按键控制与非阻塞

---

## 回顾

#### GPIO口的八种模式：

| 模式     | 描述                             |
| -------- | -------------------------------- |
| **输入** |                                  |
| 上拉输入 | 默认情况，输入高                 |
| 下拉输入 |                                  |
| 浮空输入 |                                  |
| 模拟输入 |                                  |
| **输出** |                                  |
| 推挽输出 | 0    1                           |
| 开漏输出 | 0    不能通过自身输出高电平信号1 |
| 复用推挽 |                                  |
| 复用开漏 |                                  |

#### 添加头文件路径

![image-20240331170614399](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311706471.png)

#### 模块化编程：

![image-20240331170629636](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311706684.png)

#### 函数调用：

![image-20240331170647052](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311706097.png)

![image-20240331170651659](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311706702.png)

![image-20240331170657477](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311706518.png)

---

ok，我们开始学习今天的内容

## 延时函数

单片机中延时的方法：

### 1. 空函数延时计算

空函数的执行时间取决于处理器的时钟频率。假设处理器的时钟频率为72MHz（即每秒钟执行7200万次指令），我们可以通过空函数来实现延时。

首先，我们知道执行1个空函数所需的时间是多少：

![image-20240331172333722](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311813996.png)

然后，我们想要实现1微秒的延时，所以我们需要执行的空函数次数可以通过以下计算得到：

![image-20240331172359072](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311813910.png)

所以，你需要大约72个空函数来实现1微秒的延时。



那么我们为了方便把你的写法，就定义函数来实现延时

```c
void Delay_lus(void)
{
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}
```

这样子就可以轻松实现1微秒的延时

那么纳秒和毫秒函数的写法也就很简单了



```c
//毫秒
void Delay_us(uint32_t time)
{
	while(time--)
	{
		Delay_lus();
	}
}
//微秒
void Delay_ms(uint32_t time)
{
	while(time--)
	{
		Delay_us(1000);
	}
}
```



### 2. 定时器延时

定时器延时是一种更精确和可控的延时方法。通过配置定时器，可以生成精确的时间间隔，而不受CPU负载和其他因素的影响。这使得定时器延时比简单的空函数延时更加可靠和准确。

我们后面会讲到，这里先不展开



---

## 按键控制

> 人机交互的接口

 我们所使用的板子上一共有四个按钮，我们来看看电路图

![image-20240331173233530](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311732565.png)

我们要使用按钮，第一步一定是初始化

```c
void KET_Config()
{
	//KEY1 --paPA0
	//KEY2 --paPC5
	//KEY3 --paPC6
  //浮空输入
	//step1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA,ENABLE);
	
	//step2.配置IO口模式
	GPIO_InitTypeDef	GPIO_InitSTRUCT;
	GPIO_InitSTRUCT.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitSTRUCT.GPIO_Speed = GPIO_Speed_50MHz;
	
	//step3.初始化IO口
	GPIO_Init(GPIOA,&GPIO_InitSTRUCT);
	
	GPIO_InitSTRUCT.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	
	GPIO_Init(GPIOC,&GPIO_InitSTRUCT);
}
```

那接下来，我们自然要判断按钮是否被按下

我们只需要判断电平是否为高

> 不要忘了消抖哦

```c
//按键检测
uint8_t KEY_Check(void)
{
	//按键检测
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
		{
			Delay_ms(15);
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
			{
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
				{}
				return 1;
			}
		}
		return 0;
}
```



好的，这个时候我们就可以去通过按钮去控制led灯的亮灭了

那么就又引出了一个新的问题

我们该如何才能用同一个按钮来控制led灯的状态反转呢？



## STM32寄存器来控制led灯状态反转

实际上我们要实现的操作很简单

我们只需要去改变小灯泡引脚的状态

如果是0就变成1，如果是1就变成0

那么该如何改变呢

很简单，实际上只有一行代码

```c
GPIOE->ODR ^=0x1<<2;
```

我们一起来看一下这行代码

- `GPIOE`: 这表示你正在操作的是GPIOE端口。
- `ODR`: 这是GPIOE端口的输出数据寄存器。
- `^=`: 这是按位异或赋值操作符，用于对变量进行按位异或运算后再赋值给自身。
- `0x1 << 2`: 这是将十六进制数1向左移动2位，相当于将二进制数`0001`左移两位，得到`0100`，即十六进制数0x4。

可能有些抽象了，那我们这么来理解

#### 首先

我们led所在的gpio状态是怎么储存的

就是使用寄存器保存，而这个寄存器名字就叫做ODR

> 名字可以在对应的技术参考手册里面查到

里面是怎么存储的呢（这里GPIOE有十六个引脚，所以我们用十六位寄存器来演示）

0000000000000000

这就代表着我们的引脚全部都是低电平

那么实际情况可能是这样子的

0010111000110110

#### 然后

我们的led灯在2号引脚，也就是倒数第3位（寄存器从0开始）

> 也许有人问为什么是倒数的位呢，其实也很简单，你写一个1当然是从最右边开始写起，进位再向前

那我们该如果只改变第三位的状态，让它反转，而且还能让别的位保持不变呢

**我们学过的知识**

```c
单目操作符			^
移位操作符			<<
```

我们就要用到单目操作符  *按位异或   相异为真*

那这里就涉及到一个小技巧，二进制数和1或都是取反，和0或都是它本身

移位操作符我们也很熟悉了，如果大家又不是很清楚的可以去看我的前几篇博客

#### 最后

那么我们直接看例子

```c
GPIOE->ODR ^=0x1<<2;
```

我们假设寄存器目前里面状态是这样子的

0010111000110110

我们需要让第三位反转电平

那么我们只需要让它和这样一串数字相或就行

0000000000000100

那我们怎么得到上面那串数字呢

我们只需要定义一串

0000000000000001

然后这串数字左移两位就ok啦

再用或来计算即可得到

0010111000110010

大家可以写一下试一下



---

明天将会更新

阻塞与非阻塞  串口通信

相关内容

