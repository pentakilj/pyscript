######## 语法
  0. 输入输出
    输入：
      输入变量：read ,若要直接在cli执行，可给整个语句加上（）,防止read隔离代码
          read a ; read -p "input >" a ;
      输入参数 or 函数传惨 $* ,$1,$2 ..
    输出： echo ; printf
    退出： exit 0 / 1 / 2 / 3 状态码

  1. 变量
    赋值  var="xxx" , 中间不留空格
      变量调用 ${var}  ${var{ 1:2}}字符串截取1-2
    数组： a=(1 2 3) (for 循环)
      取值： ${a[1]}
  2. 逻辑运算 [] or test 检测条件是否成立
    a. 执行运算 [ ] 两边预留空格
    b. 运算符 > < >= <= 比较数字
    （有时比较命令返回会有问题，返回可能为空，不是int）
      或者 -gt -lt -eq 等
      [ -e .abc ] || touch .abc   判断.abc是否存在，不存在则创建
  3. 数学运算 $[ expression ] or expr expression or let '1 + 1'
    $[1-3]  调用计算结果${ $[exp]} , 同变量一样
  4. 执行命令 `cmd` or $(cmd)
    ret=`cmd` or `cmd` ; echo $?
  5. 循环 for do done; while do done; break, continue
    for((i=0;i<=10;i++)); do date ; done
    while true;  do date ; break ; done
  6. 代码块
    （read a ;
    if [ ${a} == 1 ]; then
      echo "1" ;
    elif [ ${a} == 2 ];then
      echo "2";
    else
      echo "3" ;
    fi)
    ## case ..
   7. 函数 funciont
     function foo()
     {
       echo "foo"
     }
  8. 重定向 （文件描述符， 并发控制）
    0 stin 键盘
    1 stdout  屏幕
      > file 覆盖
      >> file 追加
    2 stderr 屏幕
      2> file or 2>> file
    同时输出1 ，2
      > file 2>&1
      > file 2>file2
    < 输入
    # 关联管道符 到 指定符号
    mkfifo /tmp/testpip ; exec 3<>/tmp/testpip
    # 关闭文件描述符的读
    echo 3<&-
    # 关闭文件描述符的写
    exec 3>&-
######### 便捷设置
1. $$ 脚本pid
2. 时间戳
  date +%s # 精度不够
  date "+%Y-%m-%d %H:%M:%S" # 不精确
    ## 精确到毫秒 （但是有误差）
    current=`date "+%Y-%m-%d %H:%M:%S"`;
    timeStamp=`date -d "${current}" +%s`;
    currentTimeStamp=$((timeStamp*1000+`date "+%N"`/1000000))
    echo ${currentTimeStamp}
  # 毫秒精度 ( 取纳秒 date '+%N' )
  date +%s%3N
  # 微秒（不确定是否精确）
  date +%s%6N
 3.随机

 4. 等待
    sleep 10
    等主进程 waits
