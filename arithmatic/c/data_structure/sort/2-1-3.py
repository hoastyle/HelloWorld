#!/usr/bin/env python

a = [1, 2, 3, 4, 5, 6, 7]
b = a

v = 4
count = 0

for i in range(0, len(a)):
	if a[i] == v:
		v = 'NIL'
		break
	count = count + 1
	if count == 7:
		v = 'NIL'

print i, v

v = 8

for i in range(0, len(a)):
	if a[i] == v:
		v = 'NIL'
		break
	count = count + 1
	if count == 7:
		v = 'NIL'

print i, v
