# !/bin/bash
# _*_ coding:utf-8 _*_ 
#2017-2-16


import os
import urllib2
#import BZ17173

#保存文件 类
class NetFile(object):
    # 重新定义名字 适用于 linux ‘/’
    def filename(self,path,numberofurl):
        path = path.strip()
        # 直接在文件名中写入路径
        filename = path + '/' + path + str(numberofurl) + '.jpg'
        return filename

    # 保存文件
    def saveimg(self, url, filename):
        # 若存在，则跳过
        if not os.path.exists(filename):
            # 打开网络img
            file_content = urllib2.urlopen(url)
            data = file_content.read()
            the_file = open(filename, 'wb')
            the_file.write(data)
            the_file.close()
            print filename, ' is saving...'
        else:
            print 'Already exists, contine to the next...'
    
    # 判断 新建目录    
    def makedir(self, pathname):
        path = pathname.strip()
        path = pathname
        # 不存在，则创建目录
        isExists = os.path.exists(path)
        if not isExists:
            os.makedirs(path)
            print 'Creating folder %s ....' % path
            return True
        else:
            return False
            
#BZ = BZ17173.BZat17173('http://news.17173.com/gameview/wallpaper/index.shtml')
#MainPage = BZ.getMainPage()
#print BZ.getMainPage()
#urls, names = BZ.getSubPagesUrls_Names(MainPage)
#print BZ.getSubpages(subpagesurls[0])
#single_time_urls = BZ.getImgUrl(urls[0])
#print single_time_urls
#Files = NetFile()
#Files.makedir(names[0])
#for i in range(len(single_time_urls)):
#    filename = Files.filename(names[0],i+1)
#    Files.saveimg(single_time_urls[i],filename)
    


