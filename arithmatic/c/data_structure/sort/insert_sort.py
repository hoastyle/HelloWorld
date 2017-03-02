#!/usr/bin/env python

a = [0, 3, 1, 2, 5, 4]

for i in range(2,6):
	key = a[i]
	j = i - 1
#	for j in range(i-1, 0):
	while j > 0:
		print j
		if key < a[j]:
			a[j + 1] = a[j]
		else:
			break
		j = j-1
		a[j + 1] = key

print a

for i in range(2,6):
	key = a[i]
	j = i - 1
#   for j in range(i-1, 0):
	while j > 0:
		print j
		if key > a[j]:
			a[j + 1] = a[j]
		else:
			break
		j = j-1
		a[j + 1] = key

print a
