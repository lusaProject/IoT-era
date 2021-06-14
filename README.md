# HttpWebServer
HttpWebServer是一个高性能的HTTP的web服务器

## Deepin(uos) 安装MySQL

### 添加阿里的镜像源

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

### 参考连接https://blog.csdn.net/weixx3/article/details/80782479