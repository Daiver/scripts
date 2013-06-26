
import sys

import cv

from letterdetect import *

from Network.Network import *

size = (10, 15)#size of image for NN

def GetInp(image, size):#convert image to list of features for NN    
    newimg = cv.CreateImage(size, image.depth, image.nChannels );
    cv.Resize(image, newimg)
    image_size = cv.GetSize(newimg)
    grayscale = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(newimg, grayscale, cv.CV_RGB2GRAY)
    
    res = []

    for i in xrange(0, size[1]):
        for j in xrange(0, size[0]):
            res.append(255 - grayscale[i, j])#dark pix is more important            
    return res    


IMAGE_NAME = 'text4.jpg'

if len(sys.argv) == 2:#you can change img name
        IMAGE_NAME = sys.argv[1]

symblist = [-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]#outs names in NN
network = Network(size[0] * size[1], symblist)

image = cv.LoadImage(IMAGE_NAME)
image_size = cv.GetSize(image)

rects = FindLetters(image)#find letters

for r in rects:#draw rects around symbols
    cv.Rectangle(image, r[0], r[1], (0, 0, 255))
    
images = GetLetters(image)#split image to symbols images

cv.ShowImage('img', image)
print 'press any key'
cv.WaitKey(100000)

print 'Number of images:', len(images)

#10 samples for learning
print 'Start learning'
for i in xrange(0, 10):
    network.Study(GetInp(images[i], size), i % 10)

print 'finish learning'

#prediction by NN
for i in xrange(0, 70):
    cv.ShowImage('img', images[i])
    print 'Image number', i, 'of', len(images), ' prediction:', network.Handle(GetInp(images[i], size)).Value
    print 'press any key'
    cv.WaitKey(100000)

cv.WaitKey(100000)
