# !/bin/bash
# _*_ coding:utf-8 _*_
#2017-2-16

import urllib
import urllib2
import re
from random import choice

# 从网页壁纸获取的信息 类
class BZat17173(object):

    #  初始化页面
    def __init__(self, MainUrl):
        self.MainUrl = MainUrl
        self.user_agent = 'Mozilla/5.0 (Windows NT 10.0)'
        self.headers = {'User-Agent': self.user_agent}
        
    # 获取网页的内容    
    def getMainPage(self):
        try:
            #Proxylist = ['110.190.22.14:8998']
            #proxy = 'http://' + choice(Proxylist)
            #proxy_support = urllib2.ProxyHandler({'http': proxy})
            #opener = urllib2.build_opener(proxy_support)
            #urllib2.install_opener(opener)
            # 获取初始网页内容
            request = urllib2.Request(self.MainUrl, headers = self.headers)
            content = urllib2.urlopen(request)
            MainPage = content.read()
            return MainPage
        # 若连接有问题，则弹出exceptiong
        except urllib2.URLError, e:
            if hasattr(e, 'reason'):
                print "connection fail...", e.reason
                return None
                
    # 获取下一级页面的url和 对应的名字
    def getSubPagesUrls_Names(self, MainPage):
        pattern = re.compile('class="yxdy".+?<ul>(.+?)</ul>', re.S)
        #  此处只选出了一个元素 len(contents) = 1
        contents = re.findall(pattern, MainPage)
        # 筛选出 下级页面（目录） 名字
        pattern_name= re.compile('img.+?blank>(.+?)</a>', re.S)
        name = re.findall(pattern_name, contents[0])
        #print name
        # append是直接调用  WRONG
        #FolderNames = FolderNames.append(name)
        #FolderNames.append(name)
        # 筛选出 下级页面URL
        pattern_url = re.compile('<li><a href="(.+?)".+?<img', re.S)
        Url = re.findall(pattern_url, contents[0])
        #print Url
        # Wrong
        #subpagesurls = subpagesurls.append(Url)
        #subpagesurls.append(Url)
        FolderNames = name
        subpagesurls = Url
        #for i in range(len(subpagesurls)):
        #    print i, subpagesurls[i], FolderNames[i]   
        return subpagesurls, FolderNames
    
    # 读取 a subpage， 和 getMainPage功能一样
    # 方便区分吧
    def getSubpages(self, subpagesurl):
        # while
        try:
            #Proxylist = ['110.190.22.14:8998']
            #proxy = 'http://' + choice(Proxylist)
            #proxy_support = urllib2.ProxyHandler({'http': proxy})
            #opener = urllib2.build_opener(proxy_support)
            #urllib2.install_opener(opener)
            request = urllib2.Request(subpagesurl, headers = self.headers)
            content = urllib2.urlopen(request)
            subpage = content.read()
            return subpage
        except urllib2.URLError, e:
            if hasattr(e, 'reason'):
                print 'connection fail...', e.reason
                return None
    
    # 获取 下级页面有多少包含壁纸的页面
    def getsubpageNumber(self, singlepage):
        # 筛选出每个主页面有多少下级页面
        pattern = re.compile('gb-final-page-last.+?_(\d\d).shtml', re.S)
        num = re.findall(pattern, singlepage)
        #print num[0], type(num[0]), int(num[0])
        if num:
            return int(num[0])
        else:
            return 'No img in this page!'
    
    # 分割重组urls
    def getdetailUrl(self, singleurl,subpage_number):
        # 重组下级页面URL 方便循环
        lists= singleurl.split('_')
        new_url = lists[0] + '_' + str(subpage_number) + '.shtml'
        #print new_url 
        return new_url  

    # 17173 网页会不断变化？ ， 添加一个筛选函数，选用不同的pattern
    def SelectPattern(self, page):
        pattern_0 = re.compile('<p style="text-align.+?url=(.+?)" target', re.S)
        pattern_1 = re.compile('<p align="center.+?href=.+?url=(.+?)" target', re.S)
        url_0 = re.findall(pattern_0, page)
        url_1 = re.findall(pattern_1, page)
        if len(url_0) != 0:
            #print type(url_0),len(url_0)
            return url_0
        elif len(url_1) != 0:
            #print type(url_1),len(url_1)
            return url_1
    
    # 获取一个下级页面所有壁纸url             
    def getImgUrl(self,subpagesurl):
        imgurls = []
        single_urls = []
        # 下级页面内容
        page = self.getSubpages(subpagesurl)
        # 一个下级页面有多少个包含壁纸的分页面
        subpage_number = self.getsubpageNumber(page)
        if subpage_number == 'No img in this page!':
            return 'No img in this page!'
        # 重组每个分页的URL
        for i in range(1,subpage_number+1):
            #print i
            single_url = self.getdetailUrl(subpagesurl,i)
            single_urls.append(single_url)
        #print single_urls
        # 在每个分页中筛选出 壁纸URL
        for a_url in single_urls:
            single_page = self.getSubpages(a_url)
            #  一段时间后， 17173的网页会发生变化, 此部分添加到另外的函数
            #pattern_0 = re.compile('<p style="text-align.+?url=(.+?)" target', re.S)
            #pattern_1 = re.compile('<p align="center.+?href=.+?url=(.+?)" target', re.S)
            # 每个分页中有两张壁纸
            # All_url = re.findall(pattern, single_page)
            #如果urls为空，urls[0] out of range, 则需要新的pattern
            All_url = self.SelectPattern(single_page)
            # 后面存在多的无用页面，会返回None,
            if All_url:
                imgurls.append(All_url[0])
                if len(All_url) > 1:
                    imgurls.append(All_url[1])
        #print len(imgurls) 
        #for url in imgurls:
        #    print url
        return imgurls
             
#BZ = BZat17173('http://news.17173.com/gameview/wallpaper/index.shtml')
#MainPage = BZ.getMainPage()
#print BZ.getMainPage()
#subpagesurls, subpagesnames = BZ.getSubPagesUrls_Names(MainPage)
#print BZ.getSubpages(subpagesurls[0])
#single_time_urls = BZ.getImgUrl(subpagesurls[0])

