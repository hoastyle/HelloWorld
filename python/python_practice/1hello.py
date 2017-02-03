#!/usr/bin/env python
#coding=utf-8

print('hello world!')

a = 10
print(a)
print(type(a))
print(a, type(a))

a = (1, 2, 3, 4, 5)
print(a[0: -1])

def function(a, b):
	c = a**2 + b**2
	return c

a = function(1, 2)
print(a)

a = 1

def change_a(a):
	a = a + 1
	return a
change_a(a)
print a

# Leap year problem
# 哈哈
def leap(year, month, day):
	if year < 0:
		print 'year is minus'
	else:
		if((year % 100 != 0 and year % 4 == 0) or (year % 400 == 0)):
			return True
		else:
			return False
a = 1998

if leap(1998, 11, 21):
			print(a, 'true is leap year')
else:
			print(a, 'false' 'is not leap year')
