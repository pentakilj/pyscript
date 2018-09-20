1. netstate 查看绑定端口
    netstale -lntp -l listenning
    netstate -antp    -a all -n show port as number -t tcp protocal -p program
    netstate -anup   -u udp protocal

2. grep 过滤
    grep 'pt' -i file  -i ignore cases 大小写, 'pt' patten, 过滤内容
    grep 'pt' -5 file -n int number, 'pt' 前后-n行内容
    grep 'pt' -v file  -v 不匹配行

3. scp 主机间安全传递文件

4. awk

5. iptables  IP包过滤器 （防火墙）
  # 禁止IP （DROP 丢弃包， ACCEPT 通过包， QUEUE 传包到用户空间， RETURN 停止匹配此条）
  # -I insert -D delete , INPUT 入站 -s source源地址（主机名，网络名，IP）
  iptables -I INPUT -s ***.***.***.*** -j DROP
  # 封IP段
  iptables -I INPUT -s 127.0.0.0/8 -j DROP
  # 解封IP
  iptables -D INPUT -s ***.***.***.*** -j DROP
  # -A append, -L list -F flush -n 以数字打印 -C check existence -p tcp/udp  protocol
