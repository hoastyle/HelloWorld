#!/usr/bin/env python

def func(x, y=2, z=3):
	'''hello world'''
	print x, y, z

func(4)
func(4, 5, 6)
print func.__doc__
help(func)
