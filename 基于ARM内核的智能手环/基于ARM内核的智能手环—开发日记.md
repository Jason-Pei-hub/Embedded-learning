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

# DAY3

## 回顾

### 延时(delay)与时钟频率

延时(delay)操作与系统的时钟频率有关，通过nop()指令等待一定数量的时钟周期以实现延时功能。

### 定时器

定时器是一种用于在特定时间间隔内执行任务或触发事件的设备或模块。

### 按键检测

按键检测的流程包括：

1. 查看原理图，确定按键连接到哪个IO口；
2. 找到对应的IO口在硬件中的位置；
3. 分析原理图，了解按键的接线和电路连接情况。

### 按键抖动

按键抖动是指在按下或释放按键时，由于机械结构或电路原因而导致按键信号出现短暂波动。解决按键抖动的方法包括：

1. 添加适当的延时，以忽略短暂的抖动信号；
2. 在按键电路中添加电容，使抖动信号得到滤波和稳定。

---

## 时间片轮询

#### 定时器：内核定时器（滴答定时器）

![image-20240331182206988](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311822032.png)

![image-20240331182212779](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311822808.png)

1. **中断函数：** 中断函数是由硬件中断触发时执行的特殊函数。当系统中发生某些事件（例如按键按下、定时器溢出等）时，中断会打断当前的执行流程，转而执行与该中断相关的中断服务程序（ISR），执行完成后再返回到原来的执行点。

2. **时间片轮询：** 这是一种基于时间片的调度算法，用于多任务系统中。系统按照一定的时间片分配给每个任务，任务依次执行。在时间片轮询中，通常会定期检查每个任务是否需要执行，然后根据优先级和调度策略来确定下一个执行的任务。

   

#### 中断函数的特点：

* 快进快出

* 名字固定

* 无参无返

* 不建议加延时 printf函数

* 不用声明

  

**滴答定时器：**

滴答定时器（Tick Timer）是一种特殊类型的定时器，通常用于在嵌入式系统中生成精确的时间间隔。它的基本原理是在每个固定时间间隔内产生一个“滴答”信号，通过计数这些滴答信号，可以实现精确的时间测量和延时操作。

滴答定时器通常由硬件支持，它可以在芯片内部以固定的时钟频率运行。当滴答定时器启动时，它会以固定的时间间隔（通常是毫秒或微秒级别）产生一个滴答信号。这个时间间隔由定时器的时钟频率和预设的计数器值决定。

**也就是说，滴答定时器是一直在执行的，不受程序影响**



**时间片轮询基本步骤：**

1. **定义变量：** 首先，在程序中定义一个变量，用于记录时间片的状态或计数器。这个变量通常是一个全局变量。

2. **变量在对应中断服务函数里增加：** 如果使用定时器中断来实现时间片轮询，那么在定时器中断服务函数（ISR）里会对时间片计数器进行增加操作。

3. **变量外部声明：** 这个变量需要在全局范围内声明，以便在各个函数中都可以访问到它。

4. **在主函数里判断：** 在主函数（或其他需要执行轮询的地方）里，通过判断时间片计数器的值来确定是否需要执行某个任务。如果时间片计数器达到了设定的阈值，就执行相应的任务。

5. **变量清零：** 在执行完一轮时间片轮询后，需要将时间片计数器清零，以便开始下一轮的时间片计数。

   

### 实现逻辑

那么我们只需要载滴答定时器里面声明一个变量，然后滴答定时器没执行一次变量＋1

执行到特定的次数后就开始执行相应的函数 ，并清零函数

即可完成时间片轮询

```c
//滴答定时器的中断函数
void SysTick_Handler(void)
{
	LED1_TIME++;
}
```

主函数中：

```c
if(LED1_TIME >= 500)
		{
			LED1_TURN;
			LED1_TIME = 0;
			//USART1_SendStr(arr);
		}
```

这样子在我们就成功设置了状态指示灯

> 即在程序正常执行过程中led灯闪烁

---

## 串口通信

通信的类型可以根据通信的范围和介质来分类：

#### 1. 根据通信的范围：

- **局域网（LAN）：** 一种覆盖范围较小的网络，通常用于连接同一建筑物或校园内的设备。例如校园网、办公室内部网等。
- **广域网（WAN）：** 覆盖范围更广，可以连接不同地区甚至不同国家的网络，最典型的例子就是因特网。

#### 2. 根据通信的介质：

- **有线通信：** 通过物理连接来传输数据的通信方式。
  - 网线（Ethernet）：使用以太网协议进行数据传输的有线连接。
  - USB（Universal Serial Bus）：通过USB接口进行数据传输的通信方式，例如U盘。
- **无线通信：** 不需要物理连接即可传输数据的通信方式。
  - WiFi：使用无线局域网技术进行数据传输的无线连接方式。
  - 蓝牙（Bluetooth）：用于短距离数据传输的无线技术，通常用于连接手机、耳机等设备。

这些通信类型都在不同的场景下发挥作用，满足了人们在信息交流和数据传输方面的需求。

---

### 通信方式：

#### 串行通信：

- 使用单根数据线进行数据传输。
- 特点：速率相对较慢，但抗干扰能力强。

#### 并行通信：

- 使用多根数据线同时传输数据。
- 特点：速率相对较快，但抗干扰能力较弱。

### 2. 工作方式：

| 通信方式   | 特点                                                     | 举例                                 |
| ---------- | -------------------------------------------------------- | ------------------------------------ |
| 单工通信   | 只能单向传递数据，不能同时发送和接收数据。               | 麦克风和喇叭之间的通信               |
| 半双工通信 | 设备可以发送和接收数据，但同一时间只能执行其中一种操作。 | 对讲机可以让用户交替地发送和接收信息 |
| 全双工通信 | 可以同时进行数据的发送和接收。                           | 微信、打电话等通信方式               |

### 3. 同步与异步通信：

| 通信方式 | 特点                                                         | 举例             |
| -------- | ------------------------------------------------------------ | ---------------- |
| 同步通信 | 设备之间有一根同步时钟线，用于同步数据传输。数据传输的时机和速率由时钟信号控制，数据按照时钟信号进行同步传输。 | 以太网、USB      |
| 异步通信 | 设备之间没有共享的同步时钟线，数据按照起始位和停止位的规则进行传输。数据传输的时机不依赖于时钟信号，而是通过起始位和停止位来确定数据的传输时序。 | RS-232串口、UART |

### 4. 传输速率：

传输速率通常用波特率（bps）来表示，表示每秒传输的位数。

##### 常见的波特率包括：

- **115200 bps**：用于高速数据传输，例如串口通信。
- 9600 bps：用于一般数据传输，例如早期的调制解调器通信。

这些通信方式和特点在不同的应用场景中具有不同的优势和适用性。

---

## RS232协议

- **起始位**：数据传输开始的信号，由逻辑1变为逻辑0。

- **数据位**：通常为8位，表示一个字节的数据。

- 校验位

  ：可选的奇偶校验，用于检验数据位中1的个数，以确保传输的数据正确性。

  - 奇校验：校验位补充一个1，使数据位中1的个数为奇数。
  - 偶校验：校验位补充一个1，使数据位中1的个数为偶数。

- **停止位**：数据传输结束的信号，由逻辑0变为逻辑1。

  ![image-20240331184858996](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311848030.png)

### 串口

串口是一种用于串行通信的端口，常用于连接计算机与外部设备。其中：

- **TX**：发送端，负责将数据发送给外部设备。
- **RX**：接收端，负责接收外部设备发送的数据。
- **GND**：地线，用于建立电气连接并确保信号的准确传输。

串口通常用于连接设备，如串口打印机、调制解调器等，通过串行传输数据。

---

串口连接可以分为直接连接和间接连接两种方法：

### 1. 直接连接

直接连接是指将两个设备通过串口线直接相连，其中一端的发送端（TX）连接到另一端的接收端（RX），同时地线（GND）也需要连接起来。这种连接方式通常用于连接两台设备之间进行数据传输，例如连接两台计算机或者计算机与外部设备的串口连接。

![image-20240331184952319](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311915120.png)

### 2. 间接连接

间接连接是指通过中间设备或者线路进行连接，而不是直接连接两台设备。例如，可以通过串口转USB转换器将串口设备连接到计算机的USB端口，或者通过串口服务器将串口设备连接到局域网中的计算机，然后通过网络进行数据传输。这种连接方式可以扩展串口设备的连接距离，并且可以实现远程访问和控制。

一键下载电路：![image-20240331185009218](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311850251.png)

![image-20240331191212119](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311912145.png)

我们这里使用的是USART1

原因也很简单 —— 功能强大

我们来看收发器的原理图和引脚图

![image-20240331191109047](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311911088.png)

![image-20240331191112777](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311911802.png)

![image-20240331191129448](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311915409.png)



## 代码实现

那第一步一定是先初始化

```c
void USART1_Config(u32 brr)
{
	//step1.初始化IO口 PA9，PA10
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//step2.初始化USART1
	//1.开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//2.配置模式
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = brr;//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//失能硬件流控制
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//停止位1位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据位8位
	//3.初始化
	USART_Init(USART1,&USART_InitStruct);
	//4.使能
	USART_Cmd(USART1,ENABLE);
	
	
	//开启接收中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	//NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	
	NVIC_Init(&NVIC_InitStruct);
	
}
```

那么如何写一个函数用来发送数据呢

```c
void USART1_SendCh(char data)
{
	//判断上次发送是否完成
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == 0);
	USART_SendData(USART1,data);
}
```

测试完成后只能发送单个数据，那么我们再写一个发送字符串的函数

```c
void USART1_SendStr(char *p)
{
	while(*p != '\0')
	{
	  USART1_SendCh(*p);
		p++;
	}
}
```

好的，那么可以发送了，我们怎么才能直到自己成功发送了呢

我们只需要在发送之后让单片机返回我们发送的内容即可

那么我们再写一个中断函数

```c
void USART1_IRQHandler()
{
	//判断是什么中断
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == 1)
	{
	  recv = USART1->DR;
		USART1->DR = recv;
	}
}
```



### 如此我们便实现了串口的通信



---

次回预告：lcd屏幕是如何显示画面的呢？我们下次将会讲解



# DAY4

## 回顾

#### 单片机延时方法总结

1. **空函数延时(delay)**
   使用空函数来进行延时操作。简单易用，但延时时间不够精确，且阻塞式。
2. **定时器延时(delay)**
   通过定时器的计数器进行延时操作，提供精确的延时时间，但是仍为阻塞式延时。
3. **定时器中断延时**
   利用定时器中断来实现延时操作，是非阻塞式的延时方法，不会占用CPU资源。
4. **滴答定时器延时**
   利用滴答定时器实现精确的延时，可以根据需求设置不同的分频器和重装载值，是一种高精度的延时方法。

#### 定时器构造要素

- **计数器(CNT)**
  - 向上计数：0-100
  - 向下计数：100-0
  - 向上向下计数：0-100-0
- **计数频率**
  - 跟时钟频率有关，通常以 MHz 为单位
  - 分频器可以设置不同的分频比，影响计数频率
- **重装载值(ARR)**
  - 达到重装载值时，产生溢出中断，可以用来精确控制延时时间

#### 串口通信

- **类型**：串行、并行
- **工作方式**：单工、半双工、全双工
- **同步方式**：同步、异步
- **波特率**：每秒传输的位数，通常以 bps (bit/s) 为单位，如 115200 bps、9600 bps

---

## 重定向printf函数

我们通过修改printf函数的子函数来使得函数可以把打印值打印在串口上

```c
//printf重定向
int fputc(int d,FILE *f)
{
    USART1_SendCh(d);
    //只需要多加一步打印字符串到串口即可
	return d;
}
```

---

## 屏幕显示

### 屏幕种类总结

1. **OLED屏幕**：
   - **类型**：有机自发光屏幕。
   - **特点**：色彩细腻、视角广、对比度高。
   - **优点**：柔性屏幕，可以实现弯曲、折叠，显示效果好。
   - **缺点**：成本相对较高，易烧屏。
2. **LED屏幕**：
   - **类型**：LED点阵组成的显示屏。
   - **特点**：常用于广告屏、操场大屏幕等。
   - **优点**：亮度高、耐用。
   - **缺点**：单色或多色显示，不能实现像OLED那样细腻的色彩。
3. **LCD屏幕**：
   - **类型**：液晶显示屏。
   - **特点**：技术成熟，应用广泛。
   - **优点**：成本相对较低，显示稳定。
   - **缺点**：需要背光板，厚度相对较厚，视角和对比度不如OLED。
   - ![image-20240331192714772](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311927804.png)

每种屏幕类型都有其独特的特点和适用场景，选择时需要根据具体需求和预算考虑。

![image-20240331192731466](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311927497.png)

![image-20240331192737141](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311939678.png)

我们需要取模软件来显示汉字或者是图片

### 汉字取模：

![image-20240331192812682](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311928717.png)

![image-20240331192817789](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311928824.png)

![image-20240331192823173](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311928213.png)

![image-20240331192858227](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311928288.png)

### 图片取模：

![image-20240331192926180](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311929218.png)

![image-20240331192931656](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311929690.png)

然后再打开图像取模软件，导出.c文件到项目文件夹

然后定义全局变量调用

![image-20240331193038098](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311939172.png)

然后就可以显示图片了

---

## lcd屏幕

这里一直没讲怎么显示在屏幕上，是因为购买屏幕的时候商家会提供相应的函数库

如果自己写的话就太多了

![image-20240331193159229](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311931259.png)

三千多行

那么我们就可以直接去看.h文件里面声明的函数

![image-20240331193255944](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311932996.png)

如果还是不清楚就可以跳转到函数本身去看注释

> 鼠标停留在函数名上右键点击，然后点击Go To Difinition即可
>
> ![image-20240331193528590](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311935630.png)

![image-20240331193355756](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311939040.png)

这样我们就可以很便捷的使用



---

次回预告：学习如何使用时序来接受传感器的返回值

# DAY5

这次没有回顾，我们直接来看

我们使用传感器是要看**产品手册**的，那我们就来一起看看吧

![image-20240331194616476](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311946540.png)

#### 一、产品概述 

 DHT11 数字温湿度传感器是一款含有已校准数字信号输出的温湿度复合传感器。它应用专用的数 字模块采集技术和温湿度传感技术，确保产品具有枀高的可靠性与卓越的长期稳定性。传感器包括一 个电容式感湿元件和一个 NTC 测温元件，并与一个高性能 8 位单片机相连接。

#### 二、应用范围  

暖通空调、除湿器、农业、冷链仓储、测试及检测设备、消费品、汽车、自动控制、数据记录器、气 象站、家电、湿度调节器、医疗、其他相关湿度检测控制。

#### 三、产品亮点  

成本低、长期稳定、相对湿度和温度测量、品质卓越、超快响应、抗干扰能力强、超长的信号传输距 离、数字信号输出、精确校准。

> 好的，接下来才是有用的内容

#### 四、外形尺寸（单位：mm）（我们在绘制PCB板的时候能用的到）

![image-20240331195357101](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311953140.png)

1、VDD 供电 3.3～5.5V DC 

2、DATA 串行数据，单总线

3、NC 空脚 

4、GND 接地，电源负枀

#### 五、产品参数

#### 六、典型电路

![image-20240331195523175](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311955206.png)

微处理器与 DHT11 的连接典型应用电路如上图所示，DATA 上拉后与微处理器的 I/O 端口相连。 

1. 典型应用电路中建议连接线长度短于 5m 时用 4.7K 上拉电阻，大于 5m 时根据实际情况降低上拉电 阻的阻值。 

2. 使用 3.3V 电压供电时连接线尽量短，接线过长会导致传感器供电不足，造成测量偏差。 
3. 每次读出的温湿度数值是上一次测量的结果，欲获取实时数据,需连续读取 2 次，但不建议连续多次 读取传感器，每次读取传感器间隔大于 2 秒即可获得准确的数据。 
4. 电源部分如有波动，会影响到温度。如使用开关电源纹波过大，温度会出现跳动。

### 接下来是最重要的内容

> 串行通信说明（单线双向） 
>
> ◎ 单总线说明 
>
> DHT11 器件采用简化的单总线通信。单总线即只有一根数据线，系统中的数据交换、控制均由单总线 完成。
>
> 设备（主机或从机）通过一个漏枀开路或三态端口连至该数据线，以允许设备在不发送数据时能够 释放总线，而让其它设备使用总线；单总线通常要求外接一个约 4.7kΩ 的上拉电阻，这样，当总线闲置时， 其状态为高电平。由于它们是主从结极，只有主机呼叫从机时，从机才能应答，因此主机访问器件都必须 严格遵循单总线序列，如果出现序列混乱，器件将不响应主机。
>
>  ◎单总线传送数据位定义
>
>  DATA 用于微处理器与 DHT11 之间的通讯和同步,采用单总线数据格式，一次传送 40 位数据，高位先出。
>
>  数据格式: 
>
> ​			8bit 湿度整数数据 + 8bit 湿度小数数据 + 8bit 温度整数数据 + 8bit 温度小数数据 + 8bit 校验位。
>
> ​		    注：其中湿度小数部分为 0。 
>
> ◎校验位数据定义 
>
> “8bit 湿度整数数据 + 8bit 湿度小数数据 + 8bit 温度整数数据 + 8bit 温度小数数据”8bit 校验位等于 所得结果的末 8 位

| 名称     | 单总线格式定义                                               |
| -------- | ------------------------------------------------------------ |
| 起始信号 | 微处理器将数据总线（SDA）拉低至少18ms，通知传感器准备数据。最大不超过30ms。 |
| 响应信号 | 传感器将数据总线（SDA）拉低83µs，再拉高87µs，以响应主机的起始信号。 |
| 数据格式 | 主机发送起始信号后，传感器一次性从数据总线（SDA）串出40位数据，高位先出。 |
| 湿度     | 高位为湿度整数部分数据，低位为湿度小数部分数据。             |
| 温度     | 高位为温度整数部分数据，低位为温度小数部分数据。如果温度低位的Bit8为1，则表示负温度，否则为正温度。 |
| 校验位   | 校验位等于湿度高位加湿度低位加温度高位加温度低位。           |

#### 我们来看示例

![image-20240331200021937](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403312000974.png)

好的，也就是说我们一共会接收到十六位数据

### 我们该如何接收呢？

我们先初始化串口，但是这一次我们要传参，传1时设定模式为输出，传2时设定模式为输入

```c
void DHT11_Config(u8 i)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = (i == 1 ? GPIO_Mode_Out_PP:GPIO_Mode_IN_FLOATING);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	

	GPIO_Init(GPIOG,&GPIO_InitStruct);
}

```

#### 数据时序图

用户主机（MCU）发送一次开始信号后，DHT11 从低功耗模式转换到高速模式，待主机开始信号结束 后，DHT11 发送响应信号，送出 40bit 的数据，并触发一次信采集。信号发送如图所示。

![image-20240331200142563](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403312023534.png)

### 步骤一: 

DHT11 上电后（DHT11 上电后要等待 1S 以越过不稳定状态在此期间不能发送任何指令），测试环境 温湿度数据，并记录数据，同时 DHT11 的 DATA 数据线由上拉电阻拉高一直保持高电平；此时 DHT11 的 DATA 引脚处于输入状态，时刻检测外部信号。

### 步骤二: 

微处理器的 I/O 设置为输出同时输出低电平，且低电平保持时间不能小于 18ms（最大不得超过 30ms）， 然后微处理器的 I/O 设置为输入状态，由于上拉电阻，微处理器的 I/O 即 DHT11 的 DATA 数据线也随之变 高，等待 DHT11 作出回答信号，发送信号如图所示：

![](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403312005318.png)

所以我们代码实现就是这样的

```c
  //step1.起始信号
	DHT11_Config(1);
    DHT11_H;
	DHT11_L;
	Delay_ms(20);
	DHT11_H;
```

### 步骤三: 

DHT11 的 DATA 引脚检测到外部信号有低电平时，等待外部信号低电平结束，延迟后 DHT11 的 DATA 引脚处于输出状态，输出 83 微秒的低电平作为应答信号，紧接着输出 87 微秒的高电平通知外设准备接 收数据，微处理器的 I/O 此时处于输入状态，检测到 I/O 有低电平（DHT11 回应信号）后，等待 87 微秒 的高电平后的数据接收，发送信号如图所示：

![image-20240331200617269](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403312023501.png)

所以我们应该先把模式切换为输入模式

```c
//step2.响应信号
DHT11_Config(2);
```

然后去等待高电平和低电平

> 这一步不是很好理解，我们要过掉低电平和高电平，所以要先等待高电平再等待低电平（图片最后的一小段低电平）
>
> 通过滴答定时器的计数判断程序是否出现问题

```c
//等待低电平到来
	while(DHT11_R == 1)
	{
		time1++;
		Delay_us(1);
		if(time1 >= 100)
		return 0;
	}
	time1 = 0;
	
	//等待高电平到来
	while(DHT11_R == 0)
	{
		time1++;
		Delay_us(1);
		if(time1 >= 100)
		return 0;
	}
	time1 = 0;
```

### 步骤四:

由 DHT11 的 DATA 引脚输出 40 位数据，微处理器根据 I/O 电平的变化接收 40 位数据，位数据“0” 的格式为： 54 微秒的低电平和 23-27 微秒的高电平，位数据“1”的格式为： 54 微秒的低电平加 68-74 微秒的高电平。位数据“0”、“1”格式信号如图所示：

![image-20240331200934569](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403312009599.png)

这里我们需要定义数组去存放数据(要在外部定义)

```c
u8 dht11_data[5];
```

然后就去判断我们接收到的数据是0还是1

我们先等待高电平的结束

然后等待低电平结束

然后等待30us

如果此时为高电平即为1，低电平即为0

```c
//step3.接收数据 40位 高位先出
int i = 0;
for (i = 0; i < 40; i++)
{
	while (DHT11_R == 1)
	{
		time1++;
		Delay_us(1);
		if (time1 >= 100)
			return 0;
	}
	time1 = 0;

	while (DHT11_R == 0)
	{
		time1++;
		Delay_us(1);
		if (time1 >= 100)
			return 0;
	}
	time1 = 0;

	Delay_us(30);
	//判断是1还是0
	if (DHT11_R == 1)
	{
		//写入1      i 0~39
		//              0~4
		dht11_data[i / 8] |= 0x1 << (7 - i % 8);
	}
	else if (DHT11_R == 0)
	{
		dht11_data[i / 8] &= ~(0x1 << (7 - i % 8));
	}

}
```

最后验证校验位即可

```c
	//校验
	if(dht11_data[4] == dht11_data[0] + dht11_data[1] + dht11_data[2] + dht11_data[3])//
	{

	  dht11.hum = dht11_data[0];
		dht11.tem = dht11_data[2] + dht11_data[3] / 10.0;

		return 2;
	}else
	{
	  return 1;
	}
```

完整代码

```c
void DHT11_Config(u8 i)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = (i == 1 ? GPIO_Mode_Out_PP:GPIO_Mode_IN_FLOATING);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	

	GPIO_Init(GPIOG,&GPIO_InitStruct);
}

DHT11 dht11;
//dht11_data[0] 湿度高八位
u8 dht11_data[5];

int DHT11_GetVale()
{
	u8 time1 = 0;
  //step1.起始信号
	DHT11_Config(1);
  DHT11_H;
	DHT11_L;
	Delay_ms(20);
	DHT11_H;
	//step2.响应信号
	DHT11_Config(2);
	
	//等待高电平到来
	while(DHT11_R == 1)
	{
		time1++;
		Delay_us(1);
		if(time1 >= 100)
		return 0;
	}
	time1 = 0;
	
	//等待低电平到来
	while(DHT11_R == 0)
	{
		time1++;
		Delay_us(1);
		if(time1 >= 100)
		return 0;
	}
	time1 = 0;
	//step3.接收数据 40位 高位先出
	int i = 0;
	for(i = 0;i < 40;i++)
	{
		while(DHT11_R == 1)
	  {
		  time1++;
		  Delay_us(1);
	  	if(time1 >= 100)
	  	return 0;
  	}
	  time1 = 0;
	  
		while(DHT11_R == 0)
	  {
		  time1++;
		  Delay_us(1);
	  	if(time1 >= 100)
	  	return 0;
  	}
	  time1 = 0;
		
	  Delay_us(30);
  	//判断是1还是0
	  if(DHT11_R == 1)
  	{
	  	//写入1      i 0~39
	  	//              0~4
	  	dht11_data[i/8] |= 0x1<<(7 - i % 8);
			//printf("%d",dht11_data[0/8]);
	  }else if(DHT11_R == 0)
	  {
	  	dht11_data[i/8] &= ~(0x1<<(7 - i % 8));
			//printf("%d",dht11_data[0/8]);
  	}

	}
	//校验
	if(dht11_data[4] == dht11_data[0] + dht11_data[1] + dht11_data[2] + dht11_data[3])//
	{

	  dht11.hum = dht11_data[0];
		dht11.tem = dht11_data[2] + dht11_data[3] / 10.0;

		return 2;
	}else
	{
	  return 1;
	}
}

```

此时，我们在主函数中就可以成功打印此时的温湿度了

```c
printf("hum = %dHM\r\ntem = %d°C\r\n",dht11.hum,(int)dht11.tem);
```

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

![image-20240407191538166](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071919708.png)

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

# DAY7

## RTC（实时时钟）

### 什么是RTC？

RTC是指实时时钟（Real-Time Clock），是一种能够持续跟踪时间的计时器，即使在设备断电的情况下也能保持时间的准确性。它通常用于需要准确时间记录的应用，比如计时器、日历、数据记录等。

### RTC的工作原理

RTC的核心部分是一个稳定的时钟源，它以一定的频率（比如32.768KHz）运行，并且不会因为设备断电而停止。RTC可以通过内部的计数器来记录经过的时间，从而实现持续跟踪时间的功能。

![image-20240407192522838](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071925884.png)

![image-20240407192529365](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071925404.png)

由于标准库给了，所以我们简单看一下：

## RTC配置和初始化

```
cCopy CodeExplain#include "rtc.h"

// 声明RTC配置和初始化函数
void RTC_Configuration(void);
void Time_Adjust(void);
uint32_t Time_Regulate(void);

// 定义保存当前时间的结构体变量
struct tm now_time;

// RTC配置函数
void RTC_Config(){
    // 检查RTC是否已配置
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        // RTC未配置
        printf("\r\n\n RTC not yet configured....");
        // 进行RTC配置
        RTC_Configuration();
        printf("\r\n RTC configured....");
        // 调整时间
        Time_Adjust();
        // 将配置标志写入备份寄存器
        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
    else
    {
        // RTC已配置
        // 检查复位标志位
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
        {
            printf("\r\n\n Power On Reset occurred....");
        }
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
        {
            printf("\r\n\n External Reset occurred....");
        }
        printf("\r\n No need to configure RTC....");
        // 等待RTC寄存器同步
        RTC_WaitForSynchro();
        // 启用RTC秒中断
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        RTC_WaitForLastTask();
    }
}

// RTC配置函数
void RTC_Configuration(void)
{
    // 启用PWR和BKP时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    // 允许访问BKP域
    PWR_BackupAccessCmd(ENABLE);
    // 复位备份域
    BKP_DeInit();
    // 启用LSE
    RCC_LSEConfig(RCC_LSE_ON);
    // 等待LSE就绪
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {}
    // 选择LSE作为RTC时钟源
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    // 启用RTC时钟
    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForSynchro();
    RTC_WaitForLastTask();
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    RTC_WaitForLastTask();
    RTC_SetPrescaler(32767); // RTC周期 = RTCCLK / RTC_PR = (32.768 KHz) / (32767 + 1)
    RTC_WaitForLastTask();
}

// 获取当前时间的函数
uint32_t Time_Regulate(void)
{
    // 设置当前时间
    now_time.tm_year = 2024-1900;
    now_time.tm_mon = 4-1;
    now_time.tm_mday = 2;
    now_time.tm_hour = 10;
    now_time.tm_min = 13;
    now_time.tm_sec = 0;
    return mktime(&now_time);
}

// 调整时间的函数
void Time_Adjust(void)
{
    RTC_WaitForLastTask();
    RTC_SetCounter(Time_Regulate());
    RTC_WaitForLastTask();
}
```

接着我们通过数学函数画表盘

![image-20240407193013096](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071940120.png)

```c
void showbiaopan(int hour,int min)
{
	  	
    int sx1 = 0;
    int sx2 = 0;
    int sy1 = 0;
    int sy2 = 0;
				
    int sx3 = 0;
    int sx4 = 0;
    int sy3 = 0;
    int sy4 = 0;
	
    int mx1 = 0;
    int mx2 = 0;
    int my1 = 0;
    int my2 = 0;

    int mx3 = 0;
    int mx4 = 0;
    int my3 = 0;
    int my4 = 0;

    int hx1 = 0;
    int hx2 = 0;
    int hy1 = 0;
    int hy2 = 0;

    int hx3 = 0;
    int hx4 = 0;
    int hy3 = 0;
    int hy4 = 0;
		
		
		u32 time = 0;
 
		
		while(1)
		{
			switch(KEY_Check())
			{
			  case 1:
					showyemian1(HOUR,MIN,CHOUR,CMIN);
				case 2:
					showyemian2();
				case 3:
					showyemian3(TSTEP);
				case 4:
					showyemian4();
					
					
			}
				
				
			BreatheLed();
		  if(dj>=90000)
		{
			
		dj = 0;
    LCD_ShowPicture(0,0,240,320,(u8*)gImage_daiji);
			
		
		time = RTC_GetCounter();
    now_time = *localtime(&time);
		
	  now_time.tm_min += min;
    now_time.tm_hour += hour;
		
			
	  //
		get_points_on_concentric_circles(120, 160,0,20,now_time.tm_sec%60+30, &sx3, &sy3, &sx4, &sy4);
		LCD_DrawLine((uint16_t)sx3,(uint16_t)sy3,(uint16_t)sx4,(uint16_t)sy4,0);
    get_points_on_concentric_circles(120, 160,0,117,now_time.tm_sec%60, &sx3, &sy3, &sx4, &sy4);
		LCD_DrawLine((uint16_t)sx3,(uint16_t)sy3,(uint16_t)sx4,(uint16_t)sy4,0);
		
		//
	  get_points_on_concentric_circles(120, 160,30,115,now_time.tm_min%60, &mx1, &my1, &mx2, &my2);
    get_points_on_concentric_circles(120, 160,7,30,now_time.tm_min%60, &mx3, &my3, &mx4, &my4);

    LCD_DrawLine((uint16_t)mx1,(uint16_t)my1,(uint16_t)mx2,(uint16_t)my2,2);
		LCD_DrawLine((uint16_t)mx3,(uint16_t)my3,(uint16_t)mx4,(uint16_t)my4,0);
		
		//ʱ
	  get_points_on_concentric_circles(120, 160,30,72,now_time.tm_hour%12*5+5*now_time.tm_min/60, &hx1, &hy1, &hx2, &hy2);
    get_points_on_concentric_circles(120, 160,7,30,now_time.tm_hour%12*5+5*now_time.tm_min/60, &hx3, &hy3, &hx4, &hy4);

    LCD_DrawLine((uint16_t)hx1,(uint16_t)hy1,(uint16_t)hx2,(uint16_t)hy2,3);
		LCD_DrawLine((uint16_t)hx3,(uint16_t)hy3,(uint16_t)hx4,(uint16_t)hy4,1);

		
		
		
		}
		}
    
}
```

实现效果:

![46962c1939af2e79ca84a5089ac5bf5](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071940944.jpeg)

# DAY08

## 心率模块

![image-20240407194431915](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071951965.png)

![image-20240407194435761](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071951701.png)

**输入模拟量**

![image-20240407194455450](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071951603.png)

![image-20240407194501029](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071945052.png)

## MPU6050

![image-20240407194841391](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071948426.png)

![image-20240407194846625](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071948655.png)

![image-20240407194852514](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071951501.png)

**IIC**

![image-20240407194906559](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071951343.png)

接线引脚：

![image-20240407194916887](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071949916.png)

![image-20240407194922977](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071951163.png)

![image-20240407194927694](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404071949724.png)

因为这两个模块官方都提供了详细的资料和源码，这里不再过多赘述

# 非阻塞呼吸灯

> 天才的时刻

```c
#define BreatheMax 280
void BreatheLed(void)
{
	static unsigned char B_Reverse= 0;
	static int Low_Time = 0;
	static int tem = 0;

	if(!B_Reverse)   //渐亮
	{
		tem++;					//该变量会从0~BreatheMax循环，代表PWM的周期
		if(tem > BreatheMax)
		{
			tem = 0;
			Low_Time++;  				//每BreatheMax * 10us自加1
			if(Low_Time >= BreatheMax) //限制加到BreatheMax之后跳到渐灭
			{
				B_Reverse = 1;	
			}
		}	
	}
	else		//渐灭
	{
		tem++;
		if(tem > BreatheMax)
		{
			tem = 0;
			Low_Time--;		 //每BreatheMax * 10us自减1
			if(Low_Time < 0) //限制减到0之后回到渐亮
			{
				B_Reverse = 0;
			}
		}	
	}
	/*
	以渐亮为例：
		函数是10us周期性调用
						tem：	从0~BreatheMax循环递增
		BreatheMax - Low_Time ：随着 Low_Time 的增加，因为BreatheMax是固定的，所以BreatheMax - Low_Time会减少
		例如： Low_Time = 60；BreatheMax - Low_Time = 220，
			则下列语句执行的效果就是：有220 * 10us 的时间语句条件不成立，执行 (LED0 = 1)
									   60*10us  的时间语句条件成立，	 执行 (LED0 = 0)
			灯是低电平点亮，由于高电平时间比低电平多，所以呈现灯较暗的现象，反之则亮
	*/
	(tem > BreatheMax - Low_Time)?(LED0 = 0):(LED0 = 1); //如果？前条件成立，执行(LED0 = 0)，否则执行(LED0 = 1)
}
```



这段代码实现了一个呼吸灯效果，即LED的亮度在一定时间内逐渐增加或减小。

```
#define BreatheMax 280
```

这里定义了一个常量 `BreatheMax`，用于控制呼吸灯的周期长度。在这个例子中，周期长度为 280 个单位。

```
cCopy Codestatic unsigned char B_Reverse= 0;
static int Low_Time = 0;
static int tem = 0;
```

这里定义了三个静态变量 `B_Reverse`、`Low_Time` 和 `tem`，分别用于记录呼吸灯的当前状态、低电平持续时间和计时器。

```
Explainif(!B_Reverse)   //渐亮
{
    // 渐亮时的处理
}
else    //渐灭
{
    // 渐灭时的处理
}
```

这段代码通过判断 `B_Reverse` 的值来确定当前是处于渐亮还是渐灭状态。如果 `B_Reverse` 的值为 0，则表示当前处于渐亮状态；如果为 1，则表示当前处于渐灭状态。

```
Explaintem++;                  
if(tem > BreatheMax)
{
    tem = 0;
    // 处理周期性操作
}
```

在每次调用 `BreatheLed` 函数时，计时器 `tem` 会递增。当计时器值超过呼吸灯的周期长度 `BreatheMax` 时，计时器会重置为 0，并执行相应的周期性操作。

```
ExplainLow_Time++;             
if(Low_Time >= BreatheMax) 
{
    B_Reverse = 1;   
}
```

在渐亮状态下，低电平持续时间 `Low_Time` 会逐渐增加。当低电平持续时间达到呼吸灯的周期长度 `BreatheMax` 时，说明渐亮完成，需要切换到渐灭状态，此时将 `B_Reverse` 置为 1。

```
ExplainLow_Time--;     
if(Low_Time < 0) 
{
    B_Reverse = 0;
}
```

在渐灭状态下，低电平持续时间 `Low_Time` 会逐渐减小。当低电平持续时间减少到 0 时，说明渐灭完成，需要切换到渐亮状态，此时将 `B_Reverse` 置为 0。

```
(tem > BreatheMax - Low_Time)?(LED0 = 0):(LED0 = 1);
```

这行代码控制了 LED 的亮度，根据当前的低电平持续时间 `Low_Time` 和计时器 `tem` 的值来决定 LED 的亮灭状态。当 `(tem > BreatheMax - Low_Time)` 条件成立时，LED 熄灭；否则 LED 亮起。因此，在呼吸灯的渐亮过程中，LED 会变暗；在渐灭过程中，LED 会逐渐变亮。

这样，通过调整低电平持续时间 `Low_Time` 和周期计时器 `tem` 的值，就可以实现 LED 的呼吸灯效果。



稍加改动就可以实现流水呼吸灯的效果

```c
void BreatheLed(void)
{
    static int *p = NULL; // 声明为static变量，并初始化为NULL
    static unsigned char B_Reverse= 0;
    static int Low_Time = 0;
    static int tem = 0;
    static unsigned char isCycleComplete = 0; // 跟踪灯的周期是否完成

    // 初始化 LED 为关闭状态
    LED1_OFF;
    LED2_OFF;
    LED3_OFF;
    LED4_OFF;

    // 如果p为NULL，则将其指向一个全局变量，以便在函数调用之间保持其值
    if (p == NULL) {
        static int global_p = 0; // 全局变量用于保存p的值
        p = &global_p;
    }

    if (!B_Reverse)   
    {
        tem++;                  
        if (tem > BreatheMax)
        {
            tem = 0;
            Low_Time++;             
            if (Low_Time >= BreatheMax) 
            {
                B_Reverse = 1;   
            }
        }   
    }
    else        
    {
        tem++;
        if (tem > BreatheMax)
        {
            tem = 0;
            Low_Time--;         
            if (Low_Time < 0) 
            {
                B_Reverse = 0;

                // 当前灯的周期完成
                isCycleComplete = 1;
            }
        }   
    }

    // 控制LED的呼吸效果
    switch (*p)
    {
        case 0:
            (tem > BreatheMax - Low_Time) ? LED1_OFF : LED1_ON; 
            break;
        case 1:
            (tem > BreatheMax - Low_Time) ? LED2_OFF : LED2_ON; 
            break;
        case 2:
            (tem > BreatheMax - Low_Time) ? LED3_OFF : LED3_ON; 
            break;
        case 3:
            (tem > BreatheMax - Low_Time) ? LED4_OFF : LED4_ON; 
            break;
        case 4:
            (tem > BreatheMax - Low_Time) ? LED3_OFF : LED3_ON; 
            break;
        case 5:
            (tem > BreatheMax - Low_Time) ? LED2_OFF : LED2_ON; 
            break;
        default:
            break;
    }

    // 更新p的值
    if (isCycleComplete) {
        *p = (*p + 1) % 6; // 切换到下一个灯
        isCycleComplete = 0; // 重置周期完成状态
    }
}
```

### 静态变量说明：

1. `p`：指向一个整型变量的指针。使用静态变量来保存其状态，以确保在函数调用之间保持其值。初始值为 `NULL`。
2. `B_Reverse`：用于标记呼吸灯的状态，0表示逐渐亮起，1表示逐渐变暗。
3. `Low_Time`：记录灯亮或暗的时间。
4. `tem`：用于计时，记录每次递增或递减的次数。
5. `isCycleComplete`：用于跟踪灯的周期是否完成。

### 函数主体：

1. 首先将所有 LED 关闭。
2. 如果 `p` 为 `NULL`，则将其指向一个全局变量，以便在函数调用之间保持其值。
3. 根据呼吸灯的状态逐渐调整 `Low_Time` 的值，当达到最大值或最小值时改变 `B_Reverse` 的状态，并标记当前周期完成。
4. 根据 `p` 的值控制相应的 LED 亮或暗。
5. 如果当前周期完成，则切换到下一个 LED。

### LED 控制说明：

- LED1-LED4 分别与整型变量 `p` 的值相对应，用于指示不同的灯。
- 当 `tem` 大于 `BreatheMax - Low_Time` 时，表示灯应该处于暗的状态，否则处于亮的状态。

### 备注：

- `BreatheMax` 为一个预定义的常量，表示呼吸灯的最大周期。

总的来说，该函数通过调整灯的亮度来实现 LED 的呼吸效果，并在每个周期完成时切换到下一个 LED，以实现循环呼吸的效果。



# 按键切换

```c
uint8_t KEY_Check(void)
{
    static uint8_t key_status[4] = {1, 1, 1, 1}; 
    static uint8_t key_count[4] = {0};
    uint8_t i;
    uint8_t key_press[4] = {0};

    // 检测按键状态变化
    for (i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            key_press[i] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
            break;
        case 1:
            key_press[i] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4);
            break;
        case 2:
            key_press[i] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5);
            break;
        case 3:
            key_press[i] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
            break;
        }

        if (key_press[i] != key_status[i])
        {
            key_count[i]++;
            if (key_count[i] >= check_count) // 修改此处，移除类型转换
            {
                key_status[i] = key_press[i];
                key_count[i] = 0;
            }

            if (key_press[i] == 0)
            {
                if (i == 0) // 如果按下的是按钮1
                {
                    if (key_count[i] >= long_press_count) // 判断是否长按
                    {
                        return 5; // 长按返回5
                    }
                    else
                    {
                        return i + 1; // 否则按照原逻辑返回1
                    }
                }
                else
                {
                    return i + 1; // 其他按钮按照原逻辑返回对应编号
                }
            }
        }
    }

    return 0; 
}
```

### 静态变量说明：

1. `key_status`：保存每个按键的状态，初始值为1，表示按键未按下。
2. `key_count`：保存每个按键按下的次数。
3. `key_press`：保存每个按键的按下状态，0表示按下，1表示未按下。

### 函数主体：

1. 对每个按键进行状态检测，并将结果保存在 `key_press` 数组中。

2. 如果 `key_press[i]` 与 `key_status[i]` 不相等，表示按键状态发生了变化。

3. 将相应按键计数器 `key_count[i]` 递增。

4. 如果按键计数器大于等于指定的检测次数（`check_count`），则更新按键状态并重置计数器。

5. 如果按键按下（

   ```
   key_press[i] == 0
   ```

   ）：

   - 如果是按钮1（`i == 0`），判断按键计数器是否达到长按次数（`long_press_count`）。如果达到，则返回5表示长按，否则按照原逻辑返回1。
   - 如果是其他按钮，按照原逻辑返回对应的编号。

6. 如果没有按键按下，返回0表示无按键按下。

### 主要功能：

这个函数的主要作用是检查四个按键（按钮1到按钮4）是否被按下，并确定按键的状态，包括单击和长按。

### 重要变量：

- `key_status`：保存每个按键的状态，1表示按键未按下，0表示按键被按下。
- `key_count`：记录每个按键按下的次数，用于判断是否长按。
- `key_press`：保存每个按键当前的按下状态，用于和上一次的状态比较。

### 检测按键状态：

- 对于每个按键，函数检测其当前状态是否和上一次的状态不同。
- 如果状态发生变化，就开始计数，统计按键被按下的次数。

### 判断按键事件：

- 如果按键被按下（

  ```
  key_press[i] == 0
  ```

  ）：

  - 如果是按钮1，判断按下时间是否超过了设定的长按时间，如果是则返回5，表示长按；否则返回1，表示短按。
  - 如果是其他按钮，直接返回对应的按钮编号。

- 如果没有按键被按下，返回0。

# 项目结果展示

## 待机页面

* 有开场动画

* 所有页面无操作20s自动返回待机页面

![46962c1939af2e79ca84a5089ac5bf5](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404072002288.jpg)

# 主页

* 展示时间和温度
* 到达预定时间蜂鸣器响起，按键后关闭

![image-20240407200319470](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404072015174.png)

# 心率页面

* 可以绘制心率心电图
* 显示当前的心率和相邻两次脉搏的时间间隔
* 可以根据心率范围给出提示

![image-20240407200518276](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404072015984.png)

# 计步页面

* 记录目前步数
* 记录行进距离
* 记录目标步数进度条
* 完成目标后提示

![1e768de940beb4b0b394db37096ed0e](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404072006894.jpg)

# 环境监测页面

* 实时监测温度
* 实时监测湿度
* 实时监测空气质量
* 实时监测光照强度
* 给出相关的反馈

![1e768de940beb4b0b394db37096ed0e](https://gitee.com/jason_pei/typora-bed/raw/master/image/202404072015046.jpeg)







## 源码地址：[基于ARM内核的智能手环/项目文件/STM32 · Jason Pei/嵌入式学习历程（项目） - 码云 - 开源中国 (gitee.com)](https://gitee.com/jason_pei/embedded-systems-learning/tree/master/基于ARM内核的智能手环/项目文件/STM32)

## 相关文件：[基于ARM内核的智能手环 · Jason Pei/嵌入式学习历程（项目） - 码云 - 开源中国 (gitee.com)](https://gitee.com/jason_pei/embedded-systems-learning/tree/master/基于ARM内核的智能手环)
