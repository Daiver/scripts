#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import cv
import time

image = cv.LoadImage('data6.jpg')
print image
cv.NamedWindow('Face detection', cv.CV_WINDOW_AUTOSIZE)

image_size = cv.GetSize(image)
print image_size
grayscale = cv.CreateImage(image_size, 8, 1)

storage = cv.CreateMemStorage(0)
cascade = cv.Load('frontalface10/haarcascade_frontalface_default.xml')

st = time.time()

cv.CvtColor(image, grayscale, cv.CV_RGB2GRAY)

cv.EqualizeHist(grayscale, grayscale)
faces = cv.HaarDetectObjects(image=grayscale, cascade=cascade, 
        storage=storage, scale_factor=1.2, 
        min_neighbors=2, flags=cv.CV_HAAR_DO_CANNY_PRUNING)


if faces:
    print 'face detected!'
    for i in faces:
        print i
        cv.Rectangle(image, (i[0][0], i[0][1]),
                     (i[0][0]+i[0][2], i[0][1]+i[0][3]),
                     (0, 255, 0), 3, 8, 0)

cv.ShowImage('Face detection', image)
print 'time', time.time()-st
cv.WaitKey(0)
cv.DestroyWindow('Face detection')
