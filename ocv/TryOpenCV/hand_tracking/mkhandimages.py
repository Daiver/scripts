
import cv

from random import random

from time import time

import os

whitethreshold = 0
def notCloserToWhite(pixel):
    whitethreshold = 200 #- int(100 * random())
    return whitethreshold > ((pixel[0] + pixel[1] + pixel[2]) / 3.0)

def ListFromDir(directory):
    return [directory + '/' + i for i in os.listdir(directory)]

def blackimage(image):
    size = cv.GetSize(image)
    for i in xrange(size[1]):
        for j in xrange(size[0]):
            if not notCloserToWhite(image[i, j]):
                image[i, j] = (0, 0, 0)

    return image

def AddNoise(image, threshold):
    size = cv.GetSize(image)
    for i in xrange(size[1]):
        for j in xrange(size[0]):
            if random() > threshold:
                image[i, j] = (random() * 255, random() * 255, random() * 255)

def PasteIntoBG(image, bg, featurefunc):
    size = cv.GetSize(image)
    cv.SetImageROI(bg, (0, 0, size[0], size[1]))
    newbg = cv.CreateImage(size,  8, 3)
    #print bg.depth
    
    cv.SetImageROI(bg, (0, 0, size[0], size[1]))
    cv.Copy(bg, newbg)
    cv.ResetImageROI(bg)

    for i in xrange(size[1]):
        for j in xrange(size[0]):
            if featurefunc(image[i, j]):
                newbg[i, j] = image[i, j]
    
    return newbg
    
def AddLines(image, count):
    size = cv.GetSize(image)
    for i in xrange(count):
        cv.Line(image,
                ( int(random() * size[1]), int(random() * size[0])),
                ( int(random() * size[1]), int(random() * size[0])),
                (random() * 255, random() * 255, random() * 255)
                )

def CutVerImage(image, count):
    size = cv.GetSize(image)
    res = cv.CreateImage(size, cv.IPL_DEPTH_32F, 3)

    cv.Copy(image, res)

    for i in xrange(count):
        pt1 = ( int(random() * size[1]), int(random() * size[0]))
        pt2 = (int(pt1[1] * random() * 5), int(pt1[0] * random() * 5))
        pt3 = (pt1[1] + int(pt2[1] - pt1[1]), pt1[0] + int(pt2[0] - pt1[0]))
        cv.SetImageROI(res, (pt1[1], pt1[0], int(pt2[1] - pt1[1]), int(pt2[0] - pt1[0])))
        cv.FloodFill(res, pt3 (255, 255, 255))
        cv.ResetImageROI(res)
    return res

def ProcessImage(image, bg, noiselvl, linesnum):
    #whitethreshold = 240 - int(100 * random())
    res = PasteIntoBG(image, bg, notCloserToWhite)
    
    AddLines(res, linesnum)
    AddNoise(res, noiselvl)

    return res

def Loadbgs():
    
    bgs = []
    fnames = ListFromDir('images/bg')
    
    for x in fnames:
        bgs.append(cv.LoadImage(x))
    return bgs

def LoadImages():
    res = []
    num = 16
    for i in xrange(num):
        res.append(cv.LoadImage('images/handimg/' + str(i) + '.jpg'))

    return res

def SaveImages(imgs, path):
    for i in xrange(len(imgs)):
        cv.SaveImage(path + str(i) + '.jpg', imgs[i])

bgs = ListFromDir('images/bg')# Loadbgs()

imgs = LoadImages()

numofiter = 50000

#res = []

#filelist = [os.path.abspath(i) for i in os.listdir('hand3/pos') if os.path.isfile(os.path.join('hand3/pos', i))]

for i in xrange(3016, numofiter):
    #image = imgs[]#cv.LoadImage('hand/handimg/1.jpg')

    #for j in xrange(len(imgs)):
    image = imgs[int(random() * len(imgs))]
    bgnumber = int(random() * len(bgs))
    bg = cv.LoadImage(bgs[bgnumber])
    print 'process', i, bgs[bgnumber]
    pimg = ProcessImage(image, bg, 0.95 + random() * 0.059, int(random() * 50))
    cv.SaveImage('images/pos/' + str(i) + '.jpg', pimg)
    #res.append()

#print 'writing'
#SaveImages(res, 'hand3/pos/')
