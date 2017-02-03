#!/usr/bin/env python

import sys

try:
	input = raw_input('Enter something:')
except EOFError:
	print '\nEOFError'
	exit()
except:
	print '\nother error'

print 'Done'
