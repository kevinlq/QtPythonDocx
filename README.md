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

## 项目说明

在 `C++/Qt` 中读写 `word` 可选的方案不是很多，其中之前写过一篇文章总结过一些常用的方法，实际使用过程中发现那些方案并不能满足使用，不是效率问题就是某些电脑出现奔溃问题

使用 `COM` 接口在某些电脑上如果没有安装 `Microsoft office` 会出现奔溃等异常问题，而且单次导出效率低，非常不理想，所以就有了本项目的一个想法

我们知道 `Python` 开源库非常多，而且非常容易上手，那么是否能够通过 `C++` 调用 `Python` 来实现导出 `word` 呢？答案是肯定的

考虑到 word 内容较多，目前 `C++` 和 `Python` 交互使用 `JSON` 格式，这样定制化程度更高一些，详细内容可以看 `bin/test.json` 示例字段

例子如下所示：

![mainWidget](/images/mainWidget.png)

点击「导出」后，1s 内生成对应的 `Word` 文档，实际导出效果如下所示

![result](/images/word_result2.png)

目前支持以下功能

- 支持自定义标题，包括样式、字体、对齐方式等；
- 支持插入表格，表格支持单独设置某个单元格样式，字体、颜色、是否加粗等，支持合并某个单元格；
- 支持插入图片，支持相对路径和绝对路径；

[JSON 格式说明](./doc/Json_Format.md)

## 使用指南

### 如何使用

构造脚本初始化单例类
```C++
KPythonRunScript *pRunScript = KPythonRunScript::instance("wordOperate");
```

这个类封装了调用 `Python` 的细节，使用者完全不用关系怎么调用的，只需要关注对应 `Python` 函数入参、出参即可

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

> 本人测试环境 

```C++
Qt: 5.11.2 MSVC 2015 64位  
OS: windows10 64位    
python: 310 64位  
```

### 编译&&运行

* 打开本项目源码，打开工程文件`QtPythonDocx.pro`, 选择 `Release` 模式编译构建，等待编译完成即可看到示例界面，点击导出即可看到 `word` 内容正常导出而且自动打开生成的文档

### 注意

- 一定要注意自己使用库的版本和位数，`Qt` 64 位，那么对应的 `Python` 库也要用 `64`位
- 明确自己程序运行系统，如果需要兼容 `Windows 7`，那么只能选择 `Python 3.8`版本
- 如果发现执行效果不对，或者文档没有生成，很大概率是 `Python` 报错了，建议在终端调试下 `Python` 脚本，会有详细的异常提示


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

![thanks](/images/qrcode_for_devstone.png)


查看更多关于这个项目的贡献者，请阅读 [contributors](#)

## 授权协议


这个项目 `Apache License 2.0` 协议， 请点击 [LICENSE](LICENSE) 了解更多细节

## 致谢

如果觉得分享的内容不错，欢迎 `star` 支持，有任何问题欢迎提 `issues`.


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


