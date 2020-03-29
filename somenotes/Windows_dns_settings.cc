################################  Windosw DNS ################################
######################### 配置1 #########################
# virtualbox 中配置dnsmasq和dnscrypt-proxy组合成vb 上的DNS server
# virtualbox 设置 dnsmasq 和 dnscrypt-proxy 组合不生效
# vb中的dnsmasq监听网卡有问题
################### 配置2（当前配置） ###################
2. 设置 2, 路由器中设置 dnsmasq， 监听 windows当前主机中的dnscrypt-proxy
#  重启后路由后，配置会掉， 重启windows主机，ip变化，dnscrypt-proxy配置要更新
# 路由器：监听本机IP 5300
# 主机：dnscrypt-proxy监听本机IP， 5300，dns 设置为路由器ip
# 配置内容， 日志异步，提高性能
cache-size=5000
log-queries
log-async=20
log-facility=/tmp/query.log
clear-on-reload
server=/115.com/bilibili.com/223.5.5.5
server=192.168.1.4#5300   ## 自动产生
# 重启服务
/etc/init.d/dnsmasq restart
