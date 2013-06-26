import sys

import cv

import numpy as np
 
import time

import math

import mkgrayscale as mkgr

def diffX(rect, img):
    n = rect[2] * rect[3]
    res = []
    for i in xrange(0, rect[2]):
        for j in xrange(0, rect[3]):
            res.append(img[i + rect[0], j + rect[1]] - img[i + rect[0] - 1, j + rect[1]])
    return res


def diffY(rect, img):
    n = rect[2] * rect[3]
    res = []
    for i in xrange(0, rect[2]):
        for j in xrange(0, rect[3]):
            res.append(img[i + rect[0], j + rect[1]] - img[i + rect[0], j + rect[1] -1 ])
    return res


def difftime(rect, img1, img2):
    n = rect[2] * rect[3]
    res = []
    for i in xrange(0, rect[2]):
        for j in xrange(0, rect[3]):
            try:
                res.append(img1[i + rect[0], j + rect[1]] - img2[i + rect[0], j + rect[1]])
            except:
                print i, j
                
    return res

def MkGausFromPoint(point, N, M):
    omega = 1.5
    mu = 0

    res = []
    
    f = lambda x: 1/(omega * math.sqrt(2 * math.pi) ) * math.exp (-(x**2)/2*omega **2)

    dist = lambda p1, p2: (p1[0] - p2[0])**2 + (p1[1] - p2[1])**2

    for i in xrange(N):
        for j in xrange(M):
            res.append( f(dist(point, (i, j)) ) )
            
    return res

def LucasKanade(workpoint, rect, img1, img2):
    #workpoint = features[0]
    
    timedifference = difftime(rect, img1, img2)
    Xdifference = diffX(rect, img2)
    Ydifference = diffY(rect, img2)

    W = MkGausFromPoint(workpoint, rect[2], rect[3])

    firstsq = 0
    for i in xrange(0, len(Xdifference)):
        firstsq += W[i] * Xdifference[i]**2

    secondsq = 0
    for i in xrange(0, len(Ydifference)):
        secondsq += W[i] * Ydifference[i]**2

    mixsq = 0
    for i in xrange(0, len(Ydifference)):
        mixsq += W[i] **2 * Ydifference[i] * Xdifference[i]
    
    arr = np.array([firstsq, mixsq, mixsq, secondsq]).reshape(2, 2)

    firstsq = 0
    for i in xrange(0, len(Ydifference)):
        firstsq += W[i] **2 * timedifference[i] * Xdifference[i]
    firstsq = - firstsq

    secondsq = 0
    for i in xrange(0, len(Ydifference)):
        secondsq += W[i]**2 * timedifference[i] * Ydifference[i]
    secondsq = - secondsq

    vect = np.array([firstsq, secondsq]).reshape(2, 1)
    return vect

img1 = cv.LoadImage('LCT1.png')

gray1 = mkgr.ToGray(img1)

img2 = cv.LoadImage('LCT2.png')

gray2 = mkgr.ToGray(img2)


imgsize = cv.GetSize(img1)


workpoint = (185, 147)

rect = (1, 1, imgsize[1] - 2, imgsize[0] - 2)
#rect = (workpoint[0] - 40, workpoint[1] - 40, 80, 80)

print 'image size:', imgsize
print 'rect:', rect
print 'point', workpoint


vect = LucasKanade(workpoint, rect, gray1, gray2)

print 'vect', vect

#cv.Circle(gray1, workpoint, 3 (0,255, 0))
cv.Circle (gray1, workpoint, 3, (0, 255, 0), -1, 8, 0)

newpoint = ( int(workpoint[0] + vect[0]), int(workpoint[1] + vect[1]) )
print 'new point', newpoint

cv.Circle (gray2, newpoint, 3, (0, 255, 0), -1, 8, 0)

cv.ShowImage('F', gray1)

cv.ShowImage('FF', gray2)

cv.WaitKey(0)
cv.DestroyWindow('F')
cv.DestroyWindow('FF')

