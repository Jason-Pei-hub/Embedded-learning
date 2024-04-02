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

