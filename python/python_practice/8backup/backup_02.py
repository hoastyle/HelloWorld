#!/usr/bin/env python
#coding=utf-8
# Filename: backup_01.py
# Description: backup script

# Change Log
# * Change '/' separator to os.sep for better compatibility

# 1 源：需备份文件
# 	1.1 源目录
#	1.2 备份文件名
# 2 目的：备份目标目录
# 3 备份方式
# 4 备份

# import module
import subprocess
import time
import os

# source file, list
source_list = ['/Users/Eric/Workspace/my_project/python_practice/8backup/source/a.c',
		'/Users/Eric/Workspace/my_project/python_practice/8backup/source/b.o',
		'/Users/Eric/Workspace/my_project/python_practice/8backup/source/c']
# source = ['/Users/Eric/Workspace/my_project/python_practice/8backup/source/', '1']

# target directory
target_dir = '/Users/Eric/Workspace/my_project/python_practice/8backup/dest'

# date directory
date_dir = target_dir + os.sep + time.strftime('%Y.%m.%d')

if not os.path.exists(date_dir):
	subprocess.call('mkdir %s' % date_dir, shell=True)
	print 'Success create directory', date_dir
else:
	print 'Date directory already exists'

# backup target name
target = date_dir + os.sep + time.strftime('%H:%M:%S') + '.zip'

# backup by zip
# join() usage: separator.join(list) 
# command = "zip -r '%s' %s" % (target, ' '.join(source_list))
command = "zip -r %s %s" % (target, ' '.join(source_list))

# if subprocess.call(command, shell=True) == 0:
if subprocess.call(command, shell=True) == 0:
	print 'Successful backup to', target
else:
	print 'Backup failed'
