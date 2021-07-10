#!/bin/bash

LOG_PATH="/home/cooler/log_test.log"

function log()
{
    content="$@"
    echo ${content}
    echo ${content} >>${LOG_PATH}
}

function print_nums()
{
    log $i
}

function main()
{
    [ -e ${LOG_PATH} ] || touch ${LOG_PATH}
    # 创建管道, first in, first out
    [ -e /tmp/testpip ] || mkfifo /tmp/testpip
    # 关联文件描述符 （有3-1024, ulimit -u 查看， 0,1,2内置使用
    # 不能有空格，这里是管理文件描述符
    exec 3<>/tmp/testpip
    # 可删除，内核已打开，程序结束后回收
    rm -rf /tmp/testpip
    # loop
    for((i=1;i<=10;i++))
    do
        # 写入空行，当控制令牌，读一个空行执行一个进程
        echo >&3
    done
    # main loop
    for((i=1;i<=100;i++))
    do
    # 读取空行
	read -u3
        {
    	    print_nums $i
          ret=`sleep 1 2>&1`
          log ${ret}
          # 读入一个就写入一个，保证管道流通
          echo >&3
        # { } 里面的程序块后台执行 &
        }&
        # inner var for loop change
        # loop_var=$[${i}+100]
    done
}
# 主进程
main "$@"
# 等待
wait
# 必须分开关闭
# 关闭文件描述符的读
echo 3<&-
# 关闭文件描述符的写
exec 3>&-
