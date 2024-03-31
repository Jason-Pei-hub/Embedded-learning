# DAY2

> 本次重点
>
> * STM32寄存器来控制led灯状态反转
>
> * 按键控制与非阻塞

---

## 回顾

#### GPIO口的八种模式：

| 模式         | 描述                             |
|--------------|----------------------------------|
| **输入**     |                                  |
| 上拉输入     | 默认情况，输入高                 |
| 下拉输入     |                                  |
| 浮空输入     |                                  |
| 模拟输入     |                                  |
| **输出**     |                                  |
| 推挽输出     | 0    1                           |
| 开漏输出     | 0    不能通过自身输出高电平信号1 |
| 复用推挽     |                                  |
| 复用开漏     |                                  |

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

![image-20240331172333722](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311723761.png)

然后，我们想要实现1微秒的延时，所以我们需要执行的空函数次数可以通过以下计算得到：

![image-20240331172359072](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311723105.png)

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