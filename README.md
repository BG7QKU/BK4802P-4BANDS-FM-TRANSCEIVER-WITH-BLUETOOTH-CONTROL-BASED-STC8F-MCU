#概述
该收发机可以实现在10米，6米，2米，0.7米这四个频段内进行窄带调频(NFM)通信。使用SSD1306 OLED模块作为显示。可以通过蓝牙串口透传，用APP遥控，以及通过APP来手置频（非预先写好的频道以外的其他频率）。也有PC机上的Windows控制台写频程序，可以通过串口来写频。
使用JDY-08蓝牙透传模块。配套APP是在app.wxbit.com上在线写的android程序。现在因为注册没有超过30天，不能发布在其展厅，用QQ可直接登录，无需注册。下载地址为http://qr887427.fx.sj.360.cn/qing/softDU?sid=&amp;apk=https%3A%2F%2Fapp.wxbit.com%2Fb%2Fcyzlx2&amp;name=&amp;logo=&amp;size=3551732&amp;ref=seapk&amp;sign=d99f50e353815caf525bdfc3d49b0209&amp;v=140121">http://qr887427.fx.sj.360.cn/qing/softDU?sid=&amp;apk=https%3A%2F%2Fapp.wxbit.com%2Fb%2Fcyzlx2&amp;name=&amp;logo=&amp;size=3551732&amp;ref=seapk&amp;sign=d99f50e353815caf525bdfc3d49b0209&amp;v=140121
硬件参考电路图过几天整理好之后上传。
# 以下内容是这里用到的WzSerialPort库源作者的说明，注意Windows控制台上位机写频程序不能用DEV C++来编译，如果电脑不嫩用VS，用C-Free就可以

*源码为UTF-8带BOM格式，建议用该编码格式打开*



**Windows、Linux上的C++串口库，封装系统的原生API**

**参考本项目使用**

---

## Windows上常见问题：
* 在Windows上，要打开COM10以后的串口（包括COM10），串口名称不再是“COM10”，而是“\\\\.\\COM10”，因此在open函数中，如果是COM10及以后的串口，串口名（假设当前要打开COM10）应该写“\\\\\\\\.\\\\COM10”，其中“\\\\\\\\.\\\\”为“\\\\.\\”的转义。
* 在visual studio的项目中，编译报错，错误指向WzSerialPort.cpp的157行、211行的问题：
``` cpp
157|    m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, L"WriteEvent");
```
``` cpp
211|    m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, L"ReadEvent");
```
&emsp;&emsp;&emsp;导致这个编译报错的其实是VS的字符集设置所导致的。①将字符集改为“使用Unicode字符集”即可，②或者将 L"WriteEvent" 和 L"ReadEvent" 前面的 L 删除掉也可以。
**总而言之吧，这是微软的要求，字符集设置为 “使用Unicode字符集” 时需要加在字符串前加 L 先将 char\* 转为 wchar_t\* 再转为 LPCWSTR，字符集设置为 “使用多字节字符集” 时，则无需将 char\* 转为 wchar_t\* ，可直接转为LPCWSTR，因此无需加 L**

---

## Linux上的常见问题：
* 串口无法打开，可能是由于权限的问题，sudo一般可解决这个问题。
* 读串口的时候，有阻塞的现象，经测试，仅仅是Ubuntu18.04上出现来该问题，这可能是虚拟串口的原因，后续使用实际串口中如果仍有该问题，后续再更新...

---

## src/external_demo：
* 额外提供给大家另外一个C++使用串口的demo，基于boost的，该demo仅提供Linux下的指南，windows下当然也是可用的，需要大家自行折腾，原因是：boost在Windows下的编译，小编认为挺麻烦的，一句两句说不清楚，在Linux下就不一样了，直接源码编就行。
* 尽管该demo已经尽可能地迁就C/C++99了（基本没有在用boost的函数对象 + 绑定等特性），为了不显臃肿，还是使用了C++11的std::thread线程，有负担的话，把它就当成一种创建线程的手段好了。其实我还挺推荐线程使用我封装的库（可跨Windows和Linux平台，信号量和互斥锁同样封装了，同基于操作系统原生API封装），大家可以去尝试使用一下：[Thread_Mutex_Semaphore](https://github.com/ayowin/Thread_Mutex_Semaphore)
