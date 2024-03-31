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

![image-20240331184952319](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311849350.png)

### 2. 间接连接

间接连接是指通过中间设备或者线路进行连接，而不是直接连接两台设备。例如，可以通过串口转USB转换器将串口设备连接到计算机的USB端口，或者通过串口服务器将串口设备连接到局域网中的计算机，然后通过网络进行数据传输。这种连接方式可以扩展串口设备的连接距离，并且可以实现远程访问和控制。

一键下载电路：![image-20240331185009218](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311850251.png)

![image-20240331191212119](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311912145.png)

我们这里使用的是USART1

原因也很简单 —— 功能强大

我们来看收发器的原理图和引脚图

![image-20240331191109047](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311911088.png)

![image-20240331191112777](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311911802.png)

![image-20240331191129448](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311911488.png)



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
