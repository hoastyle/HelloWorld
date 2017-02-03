#!/usr/bin/env python
#coding=utf-8

dic = {'wangping':160, 'lianghao':170, 'liangzhongwu':180}

print dic

dic['wangping'] = 150

dic['liangjiwu'] = 190

for key in dic:
	print dic[key]
print dic.pop()

