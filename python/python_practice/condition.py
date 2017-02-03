#!/usr/bin/env python

input = int(raw_input('input integer:'))
# while input = int(raw_input('input integer:')):
while input:
	if input == 1:
		print 'if\n'
	elif input == 2:
		print 'elif\n'
	else:
		print 'else'
	input = int(raw_input('input integer:'))
