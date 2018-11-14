项目名称：小红书
***
项目功能：用户在小红书主页可以看到大家分享的生活经验，或者推荐的产品等形式可以是文字，图片或者产品的连接
                如果觉得分享的好可以加关注并且和关注的人聊天，用户也可以发布自己的小红书作品。  
***
小红书项目实现过程中遇到的问题？
***
1.搭建框架时： 因为之前没有接触过qt，很多地方不知道应该用什么控件，上网上查阅资料和看了视频以后，才有点明白，
                      布局的时候又花了很长的时间，最后布局布的也不是很好，不知道布局到底有什么用？
                      如何点击标签控件label弹出一个对话框 -------添加了事件
                       如何点击tableview 上的一行弹出一个对话框---------获取鼠标事件
                       还有刷新按钮没有实现。
 ***
2.连接数据库和搭建服务器时：因为当时考虑到想在Linux下写服务器（好处？），上网上查阅了资料想到了epoll加线程池的方法（好处？）
                      所以就要在Linux下连接数据库，想了一晚上整跑偏了Ubuntu下已经有它自带的数据库了因为当时不知道，以为还要像window那样，
                      走了一些弯路还好最后知道了。
 ***
3.协议包，中介者，网络epoll和线程池，把所有代码整合到一起运行的时候花了一些时间 （线程池现在还没有实现）
***
4.在qt上搭建客户端并完成注册登录时：因为服务器在Linux下客户端在window下，connect不成功，花了很长时间，现在Linux采用了桥接的方法
                                 客户端和服务器终于能连接上了，（因为要让Linux的IP暴露出来才能和别的客户端电脑通信），但是虚拟器采用桥接以后上不了网，
                               （目前还不知道怎么解决）。把虚拟机设置为桥接模式
                                 添加一个桥接的网络。用热点就能连上网，用校园网就不可以，配置的没有问题
5.在客户端注册登录时：             因为要用到多线程，不知道qt有自己的多线程，以为是和windows一样的，结果浪费了一些时间
6.在服务器端采用epoll+线程池， 在线程池添加的时候，由于一些c++的编译语法错误又花费了很长时间找错，
                                 
 **************************************************************************************************************************************************************
小红书用到了什么技术？


目前小红书
*******************************************
1.服务器是在Linux下用epoll＋线程池写的  
为什么要用epoll+线程池呢？ 首先项目的服务器在linux下想到了用epoll来实现高并发，但是发现epoll有一个缺陷，就是epoll_wait 是轮询工作的，如果发现有数据可读就处理该任务，如果任务阻塞的话，就不能轮到下一个了，还有就是epoll既做了连接判断是否有数据可读可写，还做了实际有任务到来具体的工作人物，这样的话只用一个线程来完成效率可能很低，所以想到用多线程，但是为了更好的管理线程就想到了用epoll+线程池，这样把工作任务和epoll的任务分开来做，提高了效率。
***********
epoll select poll 比较？
*******
为什么要用linux当服务器？
***********


************************************************
2.定义协议时用了协议映射表 模仿mfc的消息映射表 （代码优化，不然需要写很多的条件语句）
写了一个含有协议类型（char型的数字）和函数指针的结构体 ，定义一个这样结构体的数组，
可以通过定义宏的方式让代码更加的优化 
在处理函数的时候只需要用数组里的协议类型和传来的协议类型进行比较就好了
***********************************************
3.为了方便管理服务器代码用了makefile
***********************************************
4.客户端用的是可以跨平台的qt做界面
***************************************
5.设计模式采用了中介者模式
