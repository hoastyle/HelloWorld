#!/usr/bin/env python
#coding=utf-8

# range()
s = 'ablkajsdlg'
for i in range(1, len(s), 2):
	print s[i]

# enumerate
for (index, char) in enumerate(s):
# enumerate will output a tuple() include index and content
	print index
	print char

# zip
ta = (1, 2, 3)
tb = ('a', 'b', 'c')

zipped = zip(ta, tb)
# unzip
(a,b) = zip(*zipped)

print zipped
print (a,b)

# user defined generator
print '=====generator====='
def gen():
	a = 100
	yield a
	a = a*8
	yield a
	yield 1000

for i in gen():
	print i

# ?生成器表达式


