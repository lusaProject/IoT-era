# IoT era
## 项目简介

​		IoT era是一个轻量级高性能的HTTP的web服务器，服务开发框架是Qt和nginx组合的HTTP服务器开发框架。Nginx能够支撑5万并发连接，实际生产环境中可以支撑2~4万并发连接数，Nginx服务器，在3万并发连接下，开启10个Nginx进程消耗150MB内存。Qt 是一个优秀的 C++ 应用程序框架，在一定程度上可以获得一站式的解决方案。该项目扩展性强，根据不同的需求，配置所需的动态库。

## 程序演示

​	程序运行之后，浏览器输入 http://127.0.0.1:8080/，效果图如下：

![](resources/index.png)



 前端网页使用 H5 + JavaScript + CSS 技术， 使用渐进式开发框架vue，请求后端使用 [axios](https://www.runoob.com/vue2/vuejs-ajax-axios.html) 来完成 ajax 请求。	

![](resources/emulate.png)



## Deepin(uos) 安装MySQL

添加阿里的镜像源

deb http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse

sudo apt-key adv --recv-keys --keyserver keyserver.ubuntu.com 40976EAF437D05B5 3B4FE6ACC0B21F32

sudo apt-get install mysql-server 

sudo mysql_secure_installation

sudo mysql -uroot -p

GRANT ALL PRIVILEGES ON *.* TO root@localhost IDENTIFIED BY "123456";

##1 创建数据库weixx
CREATE DATABASE weixx;
##2 创建用户wxx(密码654321) 并允许wxx用户可以从任意机器上登入mysql的weixx数据库
GRANT ALL PRIVILEGES ON weixx.* TO wxx@"%" IDENTIFIED BY "654321"; 

安装客户端mysql数据库sudo apt-get mysql-client

安装mysql数据库开发包sudo apt-get install libmysqlclient-dev
