#### 1.  输出-打印问题
    1. requests 输出 connectionpool.py logging.info日志
      requests 中默认的logging等级为info, 可能设置了logging等级低于warning
    通过修改日志等级，或 logging.getLogger("requests").setLevel(logging.WARNING) 规避

    2.print - logging 打印顺序混乱
      print 使用的是sys.stdout, 而logging默认使用sys.stderr, 因此即便代码顺序正常，打印也
      会出席问题， 可在设置logger时指定输出方式，在import sys 后，设置
      logging.basicConfig(level=logging.info, stream=sys.stdout, format='xxx')

#### 2. 断言
    1. assert statement, statement
      assert True, 'this is false', assert 后面接当前一个语句为假时的语句，来更清晰的显示
      错误或者为假的原因或提示

    2. try-except-finally
      1. except Exception as err: raise err , 暴露可能错误，然后继续执行
      2. 此结构中定义的变量，若要每个一个语句都能识别，最好在结构外 定义（或加global)
      3. finally 放置清理或必须执行的语句

#### 3. 装饰器
    1. 统一打印日志 ， 查看输入
      def dec(foo):  # function as args to pass in
          def inner(*args, **kwargs):  # function's args
              # print args, kwargs
              foo_return = foo(*args, **kwargs) #  return foo ??foo(...)
              # print
              return foo_return

          return inner


#### 4. 内置排序（list等排序sort) sorted(iter, cmp=xx, key=xx, reverse=bool)
    传入key,对排序有权重的 可以重operator 引入 itergetter(0,1,2) 输入第几个元素的权重0>1>2
    reverse , true ,false 顺序，逆序
    key,reverse 速度快于cmp, cmp每次都会比较

#### 5. re 包 正则


#### 6. reload(sys), sys.defaultencoding('utf-8') 知道默认str<->unicode的编码器
      # coding:utf-8  定义注释，或说明中的编码
	## 脚本不使用带来
	os.environ['NO-PROXY'] = 'HOST'

#### 7. 批量调用
	key = [1, 2], map(foo, key)

#### 8. 安装 requirements.txt
	pip install -r requirement.txt
	# 对于权限有限制的可以加上 -user 仅当前用户
	# 生存requirement.txt 
	pip freeze > requirement.txt
