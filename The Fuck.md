# Linux（ubuntu）环境下部署The Fuck项目的方法（保姆级教程）

> 最近忙着研究生考试，也是很久没有写博客了，碰巧学校实训，最近Linux环境接触的比较多，就想着写这么一篇小博客来记录一下这样一个有意思的小项目

在大家使用Linux系统的时候，想必也遇到过敲好长一段命令，满心欢喜敲回车的时候却发现因为手误命令报错

那这个时候，你还要去重新检查重新修改

真的想让人喊 **FUCK！**

那碰巧GitHub上这样一个项目就解决了你喊fuck的问题，我们可以一起部署试一下

GitHub项目地址：[nvbn/thefuck：很棒的应用程序，可以纠正你之前的控制台命令。](https://github.com/nvbn/thefuck)

![带有示例的 GIF](https://raw.githubusercontent.com/nvbn/thefuck/master/example.gif)

---

## 如何安装？

其实很简单，只需要两步

1. 直接安装

   ```c
   sudo apt-get install thefuck
   ```

2. bashrc配置文件

   ```c
   #打开并编辑bashrc配置文件
   vim ~/.bashrc
   #在文件尾加入一行给thefuck取别名fuck
   eval "$(thefuck --alias fuck)"
   #使之生效
   source ~/.bashrc
   ```

找一台新电脑跟着步骤大家试验一下

### 第一步：安装

```c
sudo apt-get install thefuck
```

直接在虚拟机上面安装

![7c1ebb5c7d2284349b228f205d35a01](https://gitee.com/jason_pei/typora-bed/raw/master/image/202503051054323.png)

### 第二步：修改配置

```c
vim ~/.bashrc
```

### ![bf3d10055745ceac200845a553e0cf6](https://gitee.com/jason_pei/typora-bed/raw/master/image/202503051054059.png)

```c
#在文件尾加入一行给thefuck取别名fuck
eval "$(thefuck --alias fuck)"
```

![](https://gitee.com/jason_pei/typora-bed/raw/master/image/202503051055329.png)

### 第三步：启用配置

```c
source ~/.bashrc
```

![b0b58d7244fb6cbd51d09d0ce6bd6ee](https://gitee.com/jason_pei/typora-bed/raw/master/image/202503051057120.png)

这里可以看到报错了，上面提示缺少一个叫做distutils.spawn的模块

查了一下发现是Thefuck版本太低导致的，我们用pip升级一下thefuck版本

```c
pip install --upgrade thefuck
```



![8f1804693e6bcfd4597f83ebc4c417c](https://gitee.com/jason_pei/typora-bed/raw/master/image/202503051058887.png)

然后在运行启用配置

```c
source ~/.bashrc
```

![c15c267732b6be9f0fae9f32f45833d](https://gitee.com/jason_pei/typora-bed/raw/master/image/202503051059032.png)

成功，我们来测试一下

### 测试

我们输入ifconfig命令的时候，出现了手误

这个时候我十分气愤，于是输入了**FUCK**，愤然敲下了回车

输错的指令成功被修正

![45aae528922609ae725c402df3ce721](https://gitee.com/jason_pei/typora-bed/raw/master/image/202503051101894.png)

# 成功安装

大家可以试一试这个项目，如果出现问题也可以询问我

其他的系统可以参考原项目里的教程

GitHub项目地址：[nvbn/thefuck：很棒的应用程序，可以纠正你之前的控制台命令。](https://github.com/nvbn/thefuck)