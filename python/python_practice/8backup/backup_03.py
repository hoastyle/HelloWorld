#!/usr/bin/env python
#coding=utf-8
# Filename: backup_01.py
# Description: backup script

# Change Log
# * Add comment to zip file name

# 1 源：需备份文件
# 	1.1 源目录
#	1.2 备份文件名
# 2 目的：备份目标目录
# 3 备份方式
# 4 备份

# import module
import sys
import subprocess
import time
import os

backup_fmt = sys.argv[1]

if backup_fmt == 'list':
	print 'zip\ntar.gz'
	exit()

# source file, list
source_list = ['/Users/Eric/Workspace/my_project/python_practice/8backup/source/a.c',
		'/Users/Eric/Workspace/my_project/python_practice/8backup/source/b.o',
		'/Users/Eric/Workspace/my_project/python_practice/8backup/source/c']

# target directory
target_dir = '/Users/Eric/Workspace/my_project/python_practice/8backup/dest'

# date directory
date_dir = target_dir + os.sep + time.strftime('%Y.%m.%d')

if not os.path.exists(date_dir):
	subprocess.call('mkdir %s' % date_dir, shell=True)
	print 'Success create directory', date_dir
else:
	print 'Date directory already exists'

# acquire comment
comment = raw_input('Enter comment --> ')

if len(comment) == 0:
	target = date_dir + os.sep + time.strftime('%H:%M:%S') + '.' + backup_fmt
else:
	target = date_dir + os.sep + time.strftime('%H:%M:%S') + '_' + \
			comment.replace(' ', '_') + '.' + backup_fmt

# backup target name
# target = date_dir + os.sep + time.strftime('%H:%M:%S') + '.zip'

# backup by zip
# join() usage: separator.join(list) 
zip_command = "zip -r %s %s" % (target, ' '.join(source_list))
tar_command = "tar -czf %s %s" % (target, ' '.join(source_list))

if backup_fmt == 'zip':
	command = zip_command
elif backup_fmt == 'tar.gz':
	command = tar_command
else:
	print 'To do compressed format!'
	exit()

# if subprocess.call(command, shell=True) == 0:
if subprocess.call(command, shell=True) == 0:
	print 'Successful backup to', target
else:
	print 'Backup failed'
