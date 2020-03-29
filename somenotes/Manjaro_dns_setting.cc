#################  LINUX DNS 设置 ####################
## dig 或 drill 可检查
## 相互影响 可停止
##################
1. resolvconf
2. systemd-resolve
============================== Manaro Setting Start ==============================
============================== 1. 设置DNS ==============================
# Manjaro 默认使用NetworkManager作为网络管理，默认会覆盖 /etc/resolv.conf文件
1. 界面修改DNS
   直接在网络设置中修改
2. NetworkManager后台修改
    待定
3. 若只是不想前台修改DNS， 可修改NetworkManager的配置文件
# path:  /etc/NetworkManager/system-connections
# 编辑其中IPV4项后面的dns  多余DNS可用'#'换行注释掉
# 然后重启NetworkManager
# resolvectl flush-caches #刷新缓存DNS
# 然后开心的使用dnsproxy-proxy
==============================  2. 取消NetworkManager管理DNS ==============================
# 在NetworkManager配置文件中添加配置，取消关联
# path:  /etc/NetworkManager/conf.d/
# 配置文件中新增配置， 无，则新增配置文件
# 20-rf-manager.conf
## 默认修改那个文件etho  or wlo ??, eth0, wlo 的默认dns不一样
## resolvectr status
# 取消管理，由resolvconf管理 resolv.conf , 同时也会默认修改 resolv.conf
[main]
rc-manager=resolvconf
# 同时新建一个 任意名称的 conf ： stop_dns.conf
[main]
dns=none
============================== 3. 修改resolv.conf ==============================
# resolv.conf中的修改，默认提升会被resolvconf覆盖
1. 可向 resolf.conf 顶部插入新的DNS
# 新建文件 /etc/resolv.conf.head, 然后重启服务， 以下DNS会被插入到resolv.conf文件中
nameserver x.x.x.x
# resolvconf -u # 使/etc/resolv.conf的配置立刻生效
2. 或者直接卸载 resolvconf, 保留配置文件 resolv.conf（需要防止其他应用覆盖）
# 待更新
==============================  4. NetworkManager使用 dnsmasq 管理DNS ==============================
# 1. 设置NetworkManager的管理DNS主程序 配置文件
#  若启动dnsmasq失败, 检查配置文件的端口53 是否被占用， 关闭占用端口程序或修改配置文件的端口
# path: /etc/NetworkManager/conf.d/dns.conf # 文件名任意
###  检查 dnsmasq 配置文件语法
# 默认 dnsmasq --test     其他path
# dnsmasq --test --conf-file=/dev/null --conf-dir=/etc/NetworkManager/dnsmasq.d
[main]
dns=dnsmasq
# 新增配置到  /etc/mydns.d/
#  systemctl disable dnscrypt-proxy.service
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ dnsmasq 配置 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
######## START ###########
# 定义dnsmasq从哪里获取上游DNS服务器地址
resolv-file=/etc/mydns.d/resolv.dnsmasq.conf
# 严格按照resolv-file顺序，上到下进行DNS解析，直到地一个成功
strict-order
# 设置缓存大小 1000条，后续不用去在去服务器查询
cache-size=1000
# 定义dnsmasq监听地址，默认监控本机所有网卡
listen-address=127.0.0.1
listen-address=::1
# 设置DNS的端口，默认53, 设置为0,将禁用DNS功能
# 若修改了端口dig时要指定端口 -p 53000
# port=53000
# 指定网站使用那个DNS解析,合理配置，智能DNS加快解析速度
# 分别为国内外域名指定解析DNS, 国内 加上#port 可以指定监听dns的端口
server=/cn/bilibili.com/114.114.114.114
# 国外
server=/bing.com/1.1.1.1
# 启用泛域名解析，即：自定义解析记录，固定网站的解析地址
# address=/baidu.com/10.2.2.2
# 对于解析到此IP的域名，响应nxdomain使其失效
# 应对输入不存在的域名跳转到移动或电信的广告
# bogus-nxdomain=x.x.x.x
# 不加载本地/etc/hosts
no-hosts
# 添加额外hosts路径
addn-hosts=/etc/mydns.d/hosts
# 重启清空缓存
clear-on-reload
============================== 5. dnsmasq 配合 dnscrypt-proxy  加密DNS访问 ==============================
# 1. Arch 安装 dnscrypt-proxy , 然后启动服务
# 2. 停止系统的dns服务 systemcd-resolve
#  不停止，会导致dnsmsaq无法启动（默认使用53端口， 系统resolve占用）
  systemc disable systemd-resolve, dsiable and stop
# 3. networkmanager 不再管理dns ， /etc/NetworkManager/conf.d/*.conf
[main]
dns=none
# 4. 修改/etc/resolv.conf 注释其他nameserver ,添加以下配置
# 不会在被其他应用覆盖
nameserver 127.0.0.1
# 5. dnsmasq配置 no-resolve, 端口默认， server 监听dnscrypt-proxy的服务， 然后重启服务
# 以下为主要配置，日志、缓存等可根据上述配置自定义
listen-address=::1,127.0.0.1
no-resolv
server=::1#53000
server=127.0.0.1#53000
# 6. dnscrypt-proxy配置 ， 主要是以下配置，其他自定义，然后重启服务（主要使用.service)
listen_addresses = ['127.0.0.1:53000','[::1]:53000']
# 最后 日志开启后， 可用 journalctl -ex查看dnsmasq日志
