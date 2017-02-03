#!/usr/bin/env python

f = file('file.txt', 'w')
f.write('1line\n')
f.write('2line\n')
f.write('3line\n')
f.close()

f = file('file.txt')
while True:
	line = f.readline()
	if len(line) == 0:
		break
	print line,
f.close()
