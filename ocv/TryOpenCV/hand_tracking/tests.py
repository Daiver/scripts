
from random import random
from time import time

#my files :(
from brect import brect

def TestBRect():
    counter = 0
    maximum = 10

    num_cnst = 1000

    for i in xrange(50):
        size = (int(random() * num_cnst//2), int(random() * num_cnst//2))
        imsize = (size[0] + int(random() * num_cnst), int(size[1] + random() * num_cnst))
        pos = (int(random() * num_cnst * 2), int(random() * num_cnst * 2))
    
        rect = brect(pos, size, imsize)
        print 'im', imsize, 'pts', rect.TwoPnt(), 'rect', rect.Rect()
        if rect.Correct_Boundary(): print '!!!!!!'
        print 'check', rect.Check_Boundary(), 'rect', rect.Rect()
    

TestBRect()
