import os

from random import random

import cv

def ListFromDir(directory):
    return [directory + '/' + i for i in os.listdir(directory)]

def CutImage(image):
    old_size = cv.GetSize(image)
    new_size = (10 + int(random() * (old_size[0] - 10)), 10 + int(random() * (old_size[1] - 10)))
    dst = cv.CreateImage(new_size, 8, 3)
    start_point = (int(random() * (old_size[0] - new_size[0])), int(random() * (old_size[1] - new_size[1])))
    for i in xrange(new_size[1]):
        for j in xrange(new_size[0]):
            dst[i, j] = image[i + start_point[1], j + start_point[0]]
    return dst

def AddNoise(image, threshold):
    size = cv.GetSize(image)
    for i in xrange(size[1]):
        for j in xrange(size[0]):
            if random() > threshold:
                image[i, j] = (random() * 255, random() * 255, random() * 255)

    
def AddLines(image, count):
    size = cv.GetSize(image)
    for i in xrange(count):
        cv.Line(image,
                ( int(random() * size[1]), int(random() * size[0])),
                ( int(random() * size[1]), int(random() * size[0])),
                (random() * 255, random() * 255, random() * 255)
                )


def ProcessImage(image, noiselvl, linesnum):
    res = image
    
    AddLines(res, linesnum)
    AddNoise(res, noiselvl)

    return res


fnames = ListFromDir('images/neg')

numofiter = 50000
for i in xrange(numofiter):
    
    cur_img_num = int(random() * len(fnames))
    image = cv.LoadImage(fnames[cur_img_num])
    print i, fnames[cur_img_num]
    dst = ProcessImage(CutImage(image), 0.9 + random() * 0.099, int(random() * 100))
    cv.SaveImage('images/new_neg/' + str(i) + '_new_neg.bmp', dst)
    
    #cv.ShowImage(str(i), dst)
    #cv.WaitKey(1000)
    
print 'finish'
