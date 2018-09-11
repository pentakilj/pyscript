#### 1.  输出-打印问题
    1. requests 输出 connectionpool.py logging.info日志
      requests 中默认的logging等级为info, 可能设置了logging等级低于warning
    通过修改日志等级，或 logging.getLogger("requests").setLevel(logging.WARNING) 规避

    2.print - logging 打印顺序混乱
      print 使用的是sys.stdout, 而logging默认使用sys.stderr, 因此即便代码顺序正常，打印也
      会出席问题， 可在设置logger时指定输出方式，在import sys 后，设置
      logging.basicConfig(level=logging.info, stream=sys.stdout, format='xxx')
