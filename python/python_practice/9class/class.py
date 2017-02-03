#!/usr/bin/env python

# 1 basic class
print '======================================================='
print '1 basic class'

class new:
	pass

p = new()
print p

# 2 class function
print '\n======================================================='
print '2 class function'

class new1:
# difference between function and class function: self
	def sayHi(self):
		print 'Hello World'

p1 = new1()
p1.sayHi()

# 3 __init__
print '\n======================================================='
print '3 __init__'

class new2:
	def __init__(self, name):
		self.name = name
	def sayHi(self):
		print 'Hello World'
p2 = new2('hao')
p2.sayHi()
print p2.name

# 4 class'varible and instance's varible
print '\n======================================================='
print "4 class'varible and instance's varible"
class new3:
	'''doc of new3'''
# class's varible 
	class_var = 0

# self.name, this name is instance's varible, relate to self
	def __init__(self, name):
		# '''doc of __init__ of new3'''
		self.name = name
		new3.class_var = new3.class_var + 1
		print new3.class_var
	def __del__(self):
		print 'del'
		new3.class_var = new3.class_var - 1
		print new3.class_var
	def sayHi(self):
		'''doc of __init__ of new3'''
		print 'Hello World'

p3 = new3('hao')
# print p3.__doc__
del(p3)

#5 inheritance
print '\n======================================================='
print '5 inheritance'

class SchoolMember:
	'''Represend any school member'''
	def __init__(self, name, age):
		self.name = name
		self.age = age
		print 'Initialize SchoolMember %s' % self.name

	def tell(self):
		print 'name is %s, age is %d' % (self.name, self.age)

class Teacher(SchoolMember):
	def __init__(self, name, age, salary):
		SchoolMember.__init__(self, name, age)
		self.salary = salary
		print 'Initialize Teacher %s' % self.name

	def tell(self):
		SchoolMember.tell(self)
		print 'salary is %d' % self.salary

class Student(SchoolMember):
	def __init__(self, name, age, mark):
		SchoolMember.__init__(self, name, age)
		self.mark = mark 
		print 'Initialize Student %s' % self.name

	def tell(self):
		SchoolMember.tell(self)
		print 'mark is %d' % self.mark

t = Teacher('Sonic', 40, 40000)
s = Student('Hao', 29, 100)
t.tell()
s.tell()

mlist = [t, s]
for i in mlist:
	i.tell()
