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

![image-20240331192737141](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311927165.png)

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

![image-20240331193038098](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311930123.png)

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

![image-20240331193355756](https://gitee.com/jason_pei/typora-bed/raw/master/image/202403311933786.png)

这样我们就可以很便捷的使用



---

次回预告：学习如何使用时序来接受传感器的返回值