#!/usr/bin/env python

import cPickle as P

shoplistfile = 'shoplist.data'

shoplist = ['apple', 'mango', 'carrot']

f = file(shoplistfile, 'w')
P.dump(shoplist, f)
f.close()

del shoplist

f = file(shoplistfile, 'r')
storedlist = P.load(f)
print storedlist
