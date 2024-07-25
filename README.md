# chatserver
可以工作在nginx tcp负载均衡环境中的集群聊天服务器和客户端代码源码 基于muduo库 redis mysql实现

# nignx配置
nginx在1.9版本之前，只支持http协议web服务器的负载均衡，从1.9版本开始以后，nginx开始支持tcp的长连接负载均衡，但是nginx默认并没有编译tcp负载均衡模块，编写它时，需要加入--with-stream参数来激活这个模块。

`
nginx编译加入--with-stream参数激活tcp负载均衡模块
`

nginx编译安装需要先安装pcre、openssl、zlib等库，也可以直接编译执行下面的configure命令，根据错误提示信息，安装相应缺少的库


修改nignx.conf文件（在安装目录下的conf目录下,比如我的安装目录是/etc/nginx,那么他的配置文件就在/etc/nginx/conf目录下。 若安装目录是/usr/local/nginx,则配置文件即为/usr/local/nginx/conf目录。）
添加如下代码
![image](https://github.com/user-attachments/assets/5d578d82-3e0e-4f20-aee8-885e68b205f5)
启动nignx服务

# redis配置

`
tony@tony-virtual-machine:~$ sudo apt-get install redis-server   # ubuntu命令安装redis服务
`

ubuntu通过上面命令安装完redis，会自动启动redis服务，通过ps命令确认可以看到redis默认工作在本地主机的6379端口上。

redis支持多种不同的客户端编程语言，例如Java对应jedis、php对应phpredis、C++对应的则是
hiredis。下面是安装hiredis的步骤
![image](https://github.com/user-attachments/assets/191e877a-b4ad-45bc-ba56-79d65b3bc717)

![image](https://github.com/user-attachments/assets/d54461f6-fcf6-4679-9f9d-4c073bba53d3)

![image](https://github.com/user-attachments/assets/03436b45-602d-42c6-b40c-edef614c216b)

![image](https://github.com/user-attachments/assets/1066e261-3dfa-4ece-babb-bac0bfd5dcc0)

# 数据库设计

账户默认为'root', 密码为'123456'

![image](https://github.com/user-attachments/assets/0aa66512-bf25-4c25-97bc-d4830081f6a1)
![image](https://github.com/user-attachments/assets/8e829c36-4b68-4814-9f59-035bd2664020)

注意：表名称都为小写

# 编译启动
运行自动编译脚本 然后再bin目录中启动ChatServer
`
ChatServer 127.0.0.1 6000
`
运行第二个服务器
`
ChatServer 127.0.0.1 6002
`
而后我们可以启动客户端连接到nginx的8000端口，根据提示进用户注册或者登录聊天

`
ChatClient 127.0.0.1 8000
`




