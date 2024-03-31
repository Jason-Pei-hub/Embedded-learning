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

![image-20240331200142563](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403312001593.png)

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

![image-20240331200617269](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403312006291.png)

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

