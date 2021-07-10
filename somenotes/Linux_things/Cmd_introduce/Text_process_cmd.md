Linux中一切都是文件-file 即都可以用以下工具进行读取、处理，各有优势

1. 输出grep 过滤 （文档，日志等）
    grep 'pt' -i file  -i ignore cases 大小写, 'pt' patten, 过滤内容
    grep 'pt' -5 file -n int number, 'pt' 前后-n行内容
    grep 'pt' -v file  -v 不匹配行
    grep -A 40 'pt' file  匹配到行的后面40行
    grep -B 40 'pt' file  匹配到行前面40行
    grep -E '(a:b)' file a or b
    --binary-files=text 用zcat 等打开压缩日志，然后指定文本类型然后可以象普通文本一样过滤
    ## 正则 ^ 开头， ^$ 空行, $结尾
    grep -n 'pt' file 显示匹配的文本在文件中的行好
    grep -w 'pt' file 精确匹配，pt必须是单独存在（行首？）或非词字符之后（也是单独存在）
    grep -o 'pt' file 只显示匹配的部分（可以确认是否匹配正确）
    ## 正则 [1-9a-zA-Z]{n,m} 匹配 连续n-m个数字字母, {n} n个， \ 转义
    ## . 匹配任意非换行的字符
    ## | 或者， (a|b)c 批评 ac 或 bc  ()固定内容
    变种：
    egrep -- grep -e
    zgrep -an  --- zcat | grep -an

2. 流编辑器SET
    ### http://man.linuxde.net/sed
    # sed  流编辑器（读行， 执行单字母命令， 读行）  https://linux.cn/article-10232-1.html
    # 不接 任何参数是，sed处于显示模式，读入什么，打印什么 （内部行数是1开始）
    # 静默模式 -n （只输出匹配内容）, 如果没以静默模式执行，则将输出所以读入模式空间的内容
    sed -n input
    # 引入sedm命令  -e 接如 打印之类的命令（不是参数, 也可不接）
    sed -n -e '1p' input  #打印第一行
  # sed -n '1,3p' 打印1-3行
    # 打印命令 p  输出当前运行在模式空间的内容
    # $ 最后一行
    sed -n -e 'np' input # 打印第n行
    # 参数 -s 多个文件 （GUN）
    sed -sn -e '1p' ipunt1 input2 # 打印1,2 文件的第一行
    # 参数i 直接修改文件，而不打印
    ####### sed 命令 放在/之前，模板行首
    #  s  :  替换指定字符
    #  p  :  打印指定内容
    #  g : 替换然后写入缓存中的文本
    #  d: 删除指定内容
    ######  sed 替换标记 放在/之后， 模板行末
    # g : 行内全面替换， 若无则之替换第一个
    # p: 打印行

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
    ######### 过滤 #######
    sed -ne '/2018/12/13:14:16:01/, '/2018/12/13:13:14:50/p' file 字符串过滤
    ##### 替换文本并生效 ########
    sed -ri 's/s1/s2/g' file 匹配file中的s1并用s2替换，
		i 编辑已存在文件，r 使用扩展正则表达式
    ####  文本操作   ###
    sed 's/^/text/' host_url # 行首插入文本
    sed 's/$/&text/' host_url  #行尾插入文本. &不明
    # 合并以上命令  '/./{s/^/HEAD&/;s/$/&TAIL/}'
    sed -ri 's/^w*\.//g' host_url  # 替换为空
    ####  按行 合并文件 #####
    paste -d "ab" f1 f2 # 合并f1, f2文件，每行以ab隔开
    awk 'NR==FNR{a[NR]=$0;nr=NR;}NR>FNR{print a[NR-nr], $0}' f1 f2 # 合并f1, f2文件
    # https://blog.csdn.net/u013390088/article/details/80746461

3. awk 文本处理
  -F ‘f’ 指定分割符
  '$1="";print' # 第一行为空，正常打印其他行
  # 对输出增加时间戳，对错误输出无效
  awk '{print strftime("[%Y-%d-%m %H:%M:%S]", systime()),$0}'
  awk '{print $0}'过滤出整行 （$1地一个变量）
  NR: 当前行数（文件？）， FNR：当前文件的所在行书，直到完成后，重新计数
  NR==FNR： 处理第一个文件时， a[NR]=$0 数组a行号和内容一一对应
  nr=NR: nr记录第一个文件的行数， NR>FNR： 处理第二个文件
  a[NR-nr]: 第二个文件内容， $0 第二个文件每行的所以内容

4. column 对齐处理
  column -t
5.  nl  给文件加上行好
6.  sort 排序
    sork -k
    sork -n
7. uniq 去重
8. paste 组合文件
   paste f1 f2 同行粘贴，空格做分隔符
   paste -d '\n' f1 f2 换行粘贴，换行符做分隔符
9. wc 统计行数
   wc -l
