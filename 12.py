# coding:utf-8
import pickle, StringIO

class Person(object):
    # 自定义类型

    def __init__(self, name, address):
        self.name = name
        self.address = address

    def display(self):
        print 'name:', self.name, 'address:', self.address


jj = Person("JGood", "中国 杭州")
jj.display()
file = StringIO.StringIO()

pickle.dump(jj, file, 0)  # 序列化

print '+++++++++++++++++++++++++++++++'
print file.getvalue()   #打印序列化后的结果

print '+++++++++++++++++++++++++++++++'
# del Person #反序列的时候，必须能找到对应类的定义。否则反序列化操作失败。
file.seek(0)
jj1 = pickle.load(file)  # 反序列化 注意这里拿到的 jj1 相当于是 Person 实例了

# 见证奇迹的时刻
jj1.display()
file.close()
