#!/usr/bin/env python

filename = raw_input("Please input filename:")
file = open(filename, 'r')
for line in file:
    print line

file.close()
