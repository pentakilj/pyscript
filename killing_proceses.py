# _*_ coding:utf-8 _*_

import os
import time

names =	[
        'splayer.exe', 'TQMCenter.exe', 'tgp_daemon.exe',
        'tcls_core.exe', 'rail.exe', 'pallas.exe',
        'net_daemon.exe', 'LeagueClientUxRender.exe',
        'LeagueClientUx.exe', 'LeagueClient.exe',
        'GameLoader.exe', 'GameBarPresenceWriter.exe',
        'YY.exe', 'yybrowser.exe', 'yyplatform.exe',
        'yyqlogin.exe', 'TenioDL.exe', 'BsSndRpt.exe'
        'QQExternal.exe', 'QTalk.exe','TPHelper.exe',
        'TPWeb.exe', 'CrossProxy.exe', 'League of Legends.exe',
		'CrossUpdate.exe',
	]

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
			
def killtask(tasks):
	for task in tasks:
		print task,
		# split blank reverse index is janeral
		# id = task.split()[1]
		pid = task.split()[-2]#[1] not 
		# print pid
		os.popen('taskkill /f /im ' + pid)
		print 'Killing pid: %s'%pid

def start():
	tasks = getAliveTask()
	killtask(tasks)
	time.sleep(2)
	
start()