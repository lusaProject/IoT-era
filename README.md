# HttpWebServer
## 项目简介

​	HttpWebServer是一个高性能的HTTP的web服务器，服务开发框架是qt和nginx组合的HTTP服务器开发框架，nginx负责前端界面的get、post等请求，qt负责数据的处理和复杂的逻辑处理。组合的服务框架，避免了nginx功能限制和编译方式的繁杂。把nginx框架预先编译成动态库，当作qt模块的动态库一样。编译程序通过prf文件，查找链接所需要nginx动态库。pro工程文件包含2个子工程，分别是nginx主程序编译成执行程序，nginx请求处理的程序编译程动态库。C程序调用c++程序，使用了c++11的__cplusplus宏定义。

## 程序演示

​	如果当前环境没有配置MySQL数据库，程序编译不通过，屏蔽报错位置的代码，程序正常运行．

启动程序，浏览器输入 http://127.0.0.1:8080/，如下

![](index.png)

​	测试get请求，浏览器输入 http://127.0.0.1:8080/tp/api/get_test_tp，如下

![](get.png)

​	测试post请求，浏览器输入 http://127.0.0.1:8080/tp/api/post_test_tp，如下

![](post.png)





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

sudo apt-get mysql-client

sudo apt-get install libmysqlclient-dev
