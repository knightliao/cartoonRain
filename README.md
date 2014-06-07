CartoonRain
===========

Cartoon Rain implementation using DX9 

采用DX9的粒子系统来实现卡通雨

![](http://ww3.sinaimg.cn/bmiddle/60c9620fgw1eh4ux7mm09j20zo0ipjuf.jpg)

优酷链接：http://v.youku.com/v_show/id_XOTQ5MjQ5OTI=.html

## 项目信息 ##

- C++
- VS2012
- DirectX9

## 相关说明 ##

DX9来实现，没有SHADER代码，在RELEASE下可达到一千多帧的速度，还是不错的。

代码需要两个库文件的支持(这两个库文件都是我实现的) 

- [KnightMath.lib](https://github.com/knightliao/cg-math)(数学库)
- [KnightTrace.lib](https://github.com/knightliao/knight-trace)(调试库)

发布程序库时需要同时发布这两个库文件还有头文件。（库文件里其实就是CPP实现）

## 开发人员指南 ##

[详细设计](https://github.com/knightliao/CartoonRain/wiki/%E8%AF%A6%E7%BB%86%E8%AE%BE%E8%AE%A1)

## 缺陷 ##

没有SHADER代码，没有采用DX10