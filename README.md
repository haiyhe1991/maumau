#maumau


cocos2dx 版本 3.8.1

直接使用vs2013以上版本，打开proj.win32文件夹里面的项目文件即可

**注意，不要上传编译的临时文件**


**不要在master分支上直接开发，请新建分支，开发完成之后合并**

2015-12-06 升级引擎版本到 3.9

后续计划：
1. 由于计时器的错误，重写一部分计时器代码。
2. 不再使用过多的Scene进行切换，之后会统一一个Scene。
3. 完善自定义事件，充分解耦。


开始重写整个项目的打牌逻辑。
使用状态机机制，添加事件驱动，分离了逻辑层与显示层，代码阅读更方便合理。
重写了csv文件的读取方法，抽象了csv文件读取的父类。