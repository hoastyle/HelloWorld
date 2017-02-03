#!/usr/bin/env python
#coding=utf-8

f = open("record.txt","w")
f.writelines("tom,12,86\nlee,15,99\nlucy,11,58")
f.close()
x= open("record.txt","r")
contents=x.read()
x.close()
print contents
