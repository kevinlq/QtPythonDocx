<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/kevinlq/QtPythonDocx">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">QtPythonDocx</h3>

  <p align="center">
    QtPythonDocx
    <br />
    <a href="https://github.com/kevinlq/QtPythonDocx"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/kevinlq/QtPythonDocx">View Demo</a>
    ·
    <a href="https://github.com/kevinlq/QtPythonDocx/issues">Report Bug</a>
    ·
    <a href="https://github.com/kevinlq/QtPythonDocx/issues">Request Feature</a>
  </p>
</p>

# QtPythonDocx

> Qt calls python to implement word read and write functions。 Qt 调用 python 实现 word读写功能

**获取更多信息可以关注微信公众号：devstone**

<div align=center>
<img src="https://gitee.com/devstone/imageBed/raw/master/code/qrcode_for_devstone.png" width=20% height=20%/>

<div align=left>

## 项目说明

在 `C++/Qt` 中读写 `word` 可选的方案不是很多，其中之前写过一篇文章总结过一些常用的方法，实际使用过程中发现那些方案并不能满足使用，不是效率问题就是某些电脑出现奔溃问题

使用 `COM` 接口在某些电脑上如果没有安装 `Micro office` 会出现奔溃等异常问题，而且单次导出效率低，效果不理想，所以就有了这个想法，`Python` 现成的库非常好用，直接调用即可

`C++` 和 `Python` 交互使用 `JSON` 格式，详细内容可以看 `bin/test.json` 示例字段


![mainWidget](/images/mainWidget.png)

点击「导出」后，1s 内生成对应的 `Word` 文档，实际导出效果如下所示

![result](/images/word_result.png)

## 使用指南

### 如何使用

构造脚本初始化单例类
```C++
KPythonRunScript *pRunScript = KPythonRunScript::instance("wordOperate");
```

> 其中有个比较注意的点：python 相关虚拟机全局只需要初始化一次即可，后续重复的脚本直接调用，补充每次初始化，否则会有一些异常奔溃信息(这也算是一个坑吧)

执行脚本

```C++
bool callFun(const char *funcName,
                 const QVariantList &args = QVariantList(),
                 QVariant &returnValue = QVariant(QVariant::Invalid));
```

- funcName: python 脚本中对应的函数名字
- args: 函数入参，根据实际脚本中函数参数个数而定
- returnValue： 返回值，如果脚本函数有返回值初始化的时候赋予对应类型

```C++
def generateWord(strContent):
    #...
    return True
```
这个函数返回值是 `bool` 类型，因此调用的时候返回值值类型可以这样赋值

```C++
QVariant returnValue = false;
```

入参类型

```C++
case QVariant::String:
case QVariant::Int:    
case QVariant::Double: 
case QVariant::LongLong
case QVariant::Char:   
case QVariant::Invalid:
```

目前仅仅处理了上述类型，如果不满足需要继续扩展即可，返回值类型也类似

### 项目使用条件

Qt 5

### 如何编译

>本人测试环境  
Qt: 5.11.2 MSVC 2015 64位  
OS: windows10 64位    
python: 310 64位  
```

### 编译&&运行

* 打开本项目源码，打开工程文件`QtPythonDocx.pro`,按照下图所示进行编译配置即可：

![编译配置](/images/build_setting.png)

建议按照上述配置，添加宏定义`CONFIG+=MSVC64`

`以下以 windows 平台为例`,其他平台以我博客为主进行配置

具体针对不同平台编译宏定义不同，可以参考我这篇文章 [http://kevinlq.com/2017/09/18/Qt-black-technology/](http://kevinlq.com/2017/09/18/Qt-black-technology/)


## 贡献指南

请阅读 [CONTRIBUTING.md](#) 了解如何向这个项目贡献代码

## 版本历史

* V 0.0.1 搭建基本框架


## 关于作者

- **kevinlq**  - [kevinlq](http://kevinlq.com/)
- **GitHub**  - [kevinlq](https://github.com/kevinlq)https://github.com/kevinlq 
- **Email:** kevinlq0912@163.com
- **QQ:** 2313828706

#### <i class="fa fa-eye"></i> 若觉得对您有用,欢迎Star和Fork,可以关注公众号:

![thanks](/screen/qrcode_for_devstone.png)


查看更多关于这个项目的贡献者，请阅读 [contributors](#)

## 授权协议


这个项目 `Apache License 2.0` 协议， 请点击 [LICENSE](LICENSE) 了解更多细节

## 致谢

如果觉得分享的内容不错，可以请作者喝杯咖啡

![thanks](/screen/myCode.png)


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/kevinlq/QtPythonDocx.svg?style=for-the-badge
[contributors-url]: https://github.com/kevinlq/QtPythonDocx/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/kevinlq/QtPythonDocx.svg?style=for-the-badge
[forks-url]: https://github.com/kevinlq/QtPythonDocx/network/members
[stars-shield]: https://img.shields.io/github/stars/kevinlq/QtPythonDocx.svg?style=for-the-badge
[stars-url]: https://github.com/kevinlq/QtPythonDocx/stargazers
[issues-shield]: https://img.shields.io/github/issues/kevinlq/QtPythonDocx.svg?style=for-the-badge
[issues-url]: https://github.com/kevinlq/QtPythonDocx/issues
[license-shield]: https://img.shields.io/github/license/kevinlq/QtPythonDocx.svg?style=for-the-badge
[license-url]: https://github.com/kevinlq/QtPythonDocx/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/kevinlq


