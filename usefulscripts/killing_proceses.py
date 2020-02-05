# _*_ coding:utf-8 _*_

import os
import time

names =	[
        'splayer.exe', 'TQMCenter.exe', 'tgp_daemon.exe',
        'tcls_core.exe', 'rail.exe', 'pallas.exe',
        'net_daemon.exe', 'LeagueClientUxRender.exe', 'BackgroundTransferHost.exe',
        'LeagueClientUx.exe', 'LeagueClient.exe', 'backgroundTaskHost.exe',
        'GameLoader.exe', 'GameBarPresenceWriter.exe',
        'YY.exe', 'yybrowser.exe', 'yyplatform.exe',
        'yyqlogin.exe', 'TenioDL.exe', 'BsSndRpt.exe', 'hjGameUpdate.exe',
        'QQExternal.exe', 'QTalk.exe','TPHelper.exe',
        'TPWeb.exe', 'CrossProxy.exe', 'League of Legends.exe', 'yyassistant.exe',
        'CrossUpdate.exe', 'GoogleUpdate.exe', 'MpCmdRun.exe', 'Updater.exe',
        'GPRender.exe', 'mctoolbar.exe', 'yygame.exe', 'CrossProxy.exe',
        'DownloadSDKServer.exe', 'Thunder.exe', 'xlbrowser.exe', 'XLServicePlatform.exe',
        'QQProtect.exe', 'TASLogin.exe', 'osrss', 'QSBrowser.exe', 'QSSubProcess.exe',
		'browser.exe','railtemp30C5C962.exe','wegame.exe',
	]
# get processes
def getAliveTask():
	# wmic process get name,processid
	tasks = os.popen('tasklist /nh /svc')
	alive_task = []
	for task in tasks:
		if is_alive(task):
			alive_task.append(task)
		else: continue
	if not alive_task:
		print 'no such tasks!'
	return alive_task
# if process is alive	
def is_alive(task):
	for name in names:
		is_alive = True
		if name in task :
			# names.remove(name)
			break
		else: 
			is_alive = False
			continue
	return is_alive
# kill a process			
def killtask(tasks):
	for task in tasks:
		print task,
		# split blank reverse index is janeral
		# id = task.split()[1]
		pid = task.split()[-2]#[1] not 
		# print pid
		os.popen('taskkill /f /im ' + pid)
		print 'Killing pid: %s'%pid
# kill some services
def killservices():
    services = ['XLServicePlatform', 'QPCore']
    for svs in services:
        os.popen('net stop ' + svs)
	return None
	
def start():
	little_loop =0
	while little_loop < 3:
		print 'the %d check!\n' % little_loop
		tasks = getAliveTask()
		killtask(tasks)
		little_loop += 1
		killservices()
		time.sleep(1)
	
start()