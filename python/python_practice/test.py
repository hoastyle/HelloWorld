#!/usr/bin/env python

f = open('test.txt')
print f.next()
print f.next()
print f.next()

xl = [1,3,5]
yl = [9,12,13]
L  = [ x**2 for (x,y) in zip(xl,yl) if y > 10]
print L

re = iter(range(5))

try:
	for i in range(5):
		print re.next()
except StopIteration:
	print 'here is end', i
else:
	print 'no error'

print 'HaHaHaHa'

try:
	raise StopIteration
except StopIteration:
	print 'error'
else:
	print 'else'
finally:
	print 'finally'
