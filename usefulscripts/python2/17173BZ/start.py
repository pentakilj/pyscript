# !/bin/bash
# _*_ coding:utf-8 _*_
#2017-2-16


import BZ17173
import savefile
import time
from multiprocessing import Process,Lock

class MyProcess(Process):
    
    def __init__(self, suburl, pathname, lock):
        Process.__init__(self)
        self.suburl = suburl
        self.pathname = pathname
        self.lock = lock
        
    def run(self):   
        # 保存
        for s in range(len(self.suburl)):
            time.sleep(1)
            filename = Files.filename(self.pathname, s+1)
            # 锁进程
            self.lock.acquire()
            Files.saveimg(self.suburl[s], filename)
            # 释放进程
            self.lock.release()

def start():   
    # 初始化类   
    Files = savefile.NetFile() 
       
    UsingUrl = 'http://news.17173.com/gameview/wallpaper/index.shtml'
    # 初始化类
    bz = BZ17173.BZat17173(UsingUrl)
    # 获取主页数据
    mainpage = bz.getMainPage()
    # 从主页中获取下级页面url ，目录名字 path
    suburls, pathnames = bz.getSubPagesUrls_Names(mainpage)
    # 循环下级页面，创建目录
    for i in range(len(suburls)):
        # 第i个 suburl
        suburl = suburls[i]
        # 锁进程 
        lock = Lock()
        # img URL
        SubimgUrls = bz.getImgUrl(suburl)
        
        if SubimgUrls == 'No img in this page!':
            continue
        
        if "?" in pathnames[i]:
            pathnames[i] = pathnames[i].strip('?')
        elif "!" in pathnames[i]:
            pathnames[i] = pathnames[i].strip('!')
        
        Files.makedir(pathnames[i])
        p = MyProcess(SubimgUrls, pathnames[i], lock)
        p.start()
        p.join()
        # 用img 开启循环，保存文件
        #for s in range(len(SubimgUrls)):
            # 重新定义名字，避免重复
        #    filename = Files.filename(pathnames[i],s+1)
            # 保存文件
        #    Files.saveimg(SubimgUrls[s],filename)
        # 提示    
        print 'Done with one folder....'
        print 'This is %d folder...' % (i+1)
        time.sleep(1)
    print 'OK, all imgs downloading finished!!'

Files = savefile.NetFile()
start()

