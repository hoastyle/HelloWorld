#!/usr/bin/env python
#coding=utf-8

class Human(object):
	laugh = 'hahaha'
	weight = None
	def __init__(self, weight):
		self.weight = weight
		print 'weight is', self.weight
	def show_laugh(self):
		print self.laugh
	def lauth_100th(self):
		for i in range(10):
			self.show_laugh()

hao = Human(10)
hao.show_laugh()
hao.lauth_100th()

n1 = [1, 2, 3, 4, 5]
print n1.count(5)
