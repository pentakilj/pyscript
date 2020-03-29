############################## Docker化 DNSmasq ##############################
=============================  1. docker镜像设定 =============================
#参考github: Storytel/dnsmasq
# docker hub上star前3的
1. 构建dnsmasq镜像  Dockerfile
################ start ####################
### 基础镜像
FROM alpine:3.9
### 一层镜像，同时设置将默认dnsmasq配置改为 识别 /etc/dnsmasq 目录中的所以conf文件
RUN apk --no-cache add dnsmasq \
    && echo "conf-dir=/etc/dnsmasq,*.conf" > /etc/dnsmasq.conf
### 暴露端口
EXPOSE 53/tcp 53/udp
### 挂载点， 文件夹  可否去掉后续再看？？？
VOLUME ["/etc/dnsmasq"]
### 默认执行命令
CMD ["dnsmasq"]
################ end ####################
============================= 2. 宿主机启动及监听设定 =============================
2. host主机中设置自定义的配置文件 .conf ,用于启动容器时挂载
### 参考dnsmasq的配置 ， 同时最好加上日志
log-queries
# 挂载点的目录，后续会保存到本地host
log-facility=/etc/dnsmasq/query.log
3. 启动容器 -p后最好指定使用什么地址的端口
## 没指定具体IP时，nslookup能查询到DNS，但是ping不通，浏览器也无法解析
## 没指定时是否默认就是127.0.0.1？？？？
## -p 与 --net=host 参数冲突，只有host生效无法使用响应端口 （示例的配置呢？？)
## 后续也可以优化 /etc/resolv.conf
## 加上--restart always 故障后自动启动容器
## --dns=127.0.0.1  启动是设置dns，以免重启容器后dns回复成默认的主机映射
################ windows ################
### windows下面无法和 与dnscrypt配合使用
docker run -d --name dnsmasq \
      --cap-add=NET_ADMIN  \
      -p 127.0.0.1:53:53/tcp \
      -p 127.0.0.1:53:53/udp  \
      -v C:\Users\JACGG\dnsmasq:/etc/dnsmasq \
      dnsmasq
################ linux , 需要53端口没被占用 ################
docker run -d --name dnsmasq \
	--cap-add=NET_ADMIN \
	-p 127.0.0.1:53:53/tcp \
	-p 127.0.0.1:53:53/udp \
	-v /home/cooler/dnsmasq_docker:/etc/dnsmasq \
	--restart always dnsmasq:alpine39
## and login container , add read access to query.log for other user
chmod o+r /etc/dnsmasq/query.log
4. host主机的DNS设置为监听127.0.0.1
# 配置 /etc/resolv.conf
# 如果NetworkManager接管了dns，则要修改其中的网络链接
============================= 3. dnsmasq 容器使用的配置 =============================
#  配置了基本配置，hosts 可另外放一个conf文件到当前目录
################ dns base config #####################
# 强制使用完整的解析名
domain-needed
# 定义dnsmasq监听的地址, 127指本地缓存， 192做内网dns, 最好单独使用
# listen-address=127.0.0.1,192.168.x.x  #  监听本机则用192
###### 监听设定  重点 ######
同理 在docker 内部，则是 127（local)和172（容器内的Ip）否则外部访问不到dnsserver
# listen-address=127.0.0.1,172.17.0.2
listen-address=127.0.0.1
listen-address=::1
# 设置DNS的端口，默认53, 设置为0,将禁用DNS功能
# 若修改了端口dig时要指定端口 -p 53000
# port=53000
# hosts相关
no-hosts
# 添加其他hosts文件
# addn-hosts=/etc/dns.hosts
keep-in-foreground
#指定解析DNS文件
#resolv-file=/home/resolv.conf
# 不使用解析
no-resolv
# 配合resolv文件，严格按照resolv文件中的上下顺序解析dns
# strict-order
# 缓存
cache-size=5000
# 日志
log-queries
log-facility=/etc/dnsmasq/query.log
# 异步，提高日志记录性能, 默认为5，最大100
log-async=20
clear-on-reload
# server指定那个DNS服务器
# dns服务器， 若加上 #port 可以对dns指定端口，与dnscrypt-proxy 结合使用 但是速度较慢
# 用docker中的dnsmasq时，这里的地址需要用服务端（本地IP）192.168.x.x
# server=192.168.1.2#5300
server=127.0.0.1
# 部分域名使用特定DNS
server=/115.com/bilibili.com/223.5.5.5
server=/cn/114.114.114.114
# 类似hosts, 支持* *.115.com范解析
# address=/115.com/1.1.1.119