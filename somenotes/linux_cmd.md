1. netstate 查看绑定端口
    netstale -lntp -l listenning
    netstate -antp    -a all -n show port as number -t tcp protocal -p program
    netstate -anup   -u udp protocal

2. grep 过滤 （文档，日志等）
    grep 'pt' -i file  -i ignore cases 大小写, 'pt' patten, 过滤内容
    grep 'pt' -5 file -n int number, 'pt' 前后-n行内容
    grep 'pt' -v file  -v 不匹配行
    grep -A 40 'pt' file  匹配到行的后面40行
    grep -B 40 'pt' file  匹配到行前面40行

    # sed  流编辑器（读行， 执行单字母命令， 读行）  https://linux.cn/article-10232-1.html
    # 不接 任何参数是，sed处于显示模式，读入什么，打印什么 （内部行数是1开始）
    # 静默模式 -n （只输出匹配内容）, 如果没以静默模式执行，则将输出所以读入模式空间的内容
    sed -n input
    # 引入sedm命令  -e 接如 打印之类的命令（不是参数, 也可不接）
    sed -n -e '1p' input  #打印第一行
    # 打印命令 p  输出当前运行在模式空间的内容
    # $ 最后一行
    sed -n -e 'np' input # 打印第n行
    # 参数 -s 多个文件 （GUN）
    sed -sn -e '1p' ipunt1 input2 # 打印1,2 文件的第一行
    ####### sed 正则式
    **## ^ 行开始， $ 行结束， . 任意单个字符， [] 自定义字符集合， * 前面的模出现的次数
    sed -n -e '/sys/p' xx # 匹配包含sys的行并打印
    sed -n -e '/sys$/p' xx # 以sys结尾的行，打印
    sed -n -e '/^sys/p' xx # 以sys开头的行
    sed -n -e '/^$/p' xx # 空行
    sed -n -e '/^.$/p' xx # 仅一个字符
    sed -n -e '/./p' xx # 非空行
    sed -n -e '/a.*b/p' xx # a后有b的行
    sed -n -e '/1[0,3]/p' xx #包含1,且1后是0或3
    sed -n -e '/1[0-2]/p' xx # 0-2之间**
    #### 反斜杠 \ 转义特殊字符
    sed -ne '/\/home\/cool/p' xx # /home/cool
    或 在地一个反斜杠\加任和字符来作为分隔符 与上述命令等级
    sed -ne '\*/home/cool*p' xx # /home/cool
    ##### 参数 -E 扩展正则表达式 （sed默认只理解posix基本正则表达式）

    

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

6. date 显示特定格式的时间（ man date） （文档，日志等）
    date
    date "+%Y-%m-%d %H:%M:%S"
    date "+%Y-%b-%d %H:%M:%S"
