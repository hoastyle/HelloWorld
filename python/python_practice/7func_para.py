#!/usr/bin/env python
#coding=utf-8

# simplest function
print '\n++++++++++++++++++simplest function'
def func(a, b, c):
	print a, b, c
	return a + b + c

# default parameter passing
print func(1, 2, 3)

# keyword
print func(c = 3, b = 5, a = 8)

# keyword test
# how to handle error?
# print func(c = 3, b = 5, d = 8)
# lesson learned: the keyword should be same as function parameter

# default parameter value
print '\n++++++++++++++++++default parameter value'
def func_default(a, b, c = 10):
	print a, b, c
	return a + b + c

# default parameter value test
print func_default(5, 6)
print func_default(5, 6, )
print func_default(5, 6, 11)

# packing parameter, tuple
print '\n++++++++++++++++++dpack'
def func_pack(*para):
	print type(para)
	print para
# how to use packing parameter
	print para[1]

func_pack(1, 2, 3, 4, 5)

# dict parameter
print '\n++++++++++++++++++ddict'
def func_dict(**dict):
	print type(dict)
	print dict

func_dict(a=1, b=2, c=3)

# unpack
print '\n++++++++++++++++++dunpack'
def func_unpack(a, b, c):
	print a, b, c
	return a + b + c

tuple_para = (1, 2, 3)
print func_unpack(*tuple_para)

dict_para = {'a':1, 'b':2, 'c':3}
print func_unpack(*dict_para)


