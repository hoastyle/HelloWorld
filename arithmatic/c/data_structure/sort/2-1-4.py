#!/usr/bin/env python

a = [0, 1, 0, 1, 1, 1, 0, 1]
b = [0, 1, 1, 0, 0, 1, 0, 0]
c = [0, 0, 0, 0, 0, 0, 0, 0]

i = 7
carry = 0

while i > 0:
	print i
	if a[i] + b[i] == 0:
		c[i] = a[i] + b[i] + carry
		carry = 0
	elif a[i] + b[i] == 1:
		c[i] = a[i] + b[i] + carry
		if c[i] == 2:
			carry = 1
			c[i] = 0
		elif c[i] == 1:
			carry = 0
	elif a[i] + b[i] == 2:
		c[i] = 0 + carry
		carry = 1
	i = i - 1
	print i, c[i+1], carry

c[i] = carry

print c
