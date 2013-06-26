import sys
import cv as cv

import time

import math


def detect(image):
    image_size = cv.GetSize(image)
 
    # create grayscale version
    grayscale = cv.CreateImage(image_size, 8, 1)
    dst = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    #image[10,10] = (0, 255, 0)
#    cv.SetImageROI(image, cv.Rectangle(100, 100, 200, 200))    

    storage = cv.CreateMemStorage(0)

 
    # equalize histogram
    cv.EqualizeHist(grayscale, grayscale)

    cv.Canny(grayscale, dst, 60, 200, 3)#!!!!!
#    cv.Canny(grayscale, dst, 40, 200, 3)
    #something wrong, only 1 countuer?

    seq = cv.FindContours(dst, storage, cv.CV_RETR_CCOMP, cv.CV_CHAIN_APPROX_SIMPLE)
#    seq.sort()
#    for x in seq:
#        print x,tmpseq[0]
    print len(seq)

#    for x in seq:
#        cv.MatchShapes(x, tmpseq, cv.CV_CONTOURS_MATCH_I3)# Fail
    #cv.MatchShapes(seq, tmpseq, cv.CV_CONTOURS_MATCH_I3)# == None
    #cv.Sub(grayscale, dst, dst)
    #end wrong
    return dst

def transtemplate(template):
    image_size = cv.GetSize(template)
 
    # create grayscale version
    grayscale = cv.CreateImage(image_size, 8, 1)
    dst = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(template, grayscale, cv.CV_BGR2GRAY)
    #image[10,10] = (0, 255, 0)
    
    # create storage
    storage = cv.CreateMemStorage(0)
#    cv.ClearMemStorage(storage)
 
    # equalize histogram
    cv.EqualizeHist(grayscale, grayscale)
    dst = cv.CreateImage(image_size, 8, 1)
    cv.Canny(grayscale, dst, 200, 700, 3)

    storage = cv.CreateMemStorage(0)
    
    seq = cv.FindContours(dst, storage, cv.CV_RETR_CCOMP, cv.CV_CHAIN_APPROX_SIMPLE)

    '''seqT = 0
    perimB = 0
    for x in seq:
        perim = cv.cvContourPerimeter(x)
        if perim > perimB:
            perimB = perim
            seqT = x'''
    return dst, seq

if __name__ == "__main__":
 
    template = cv.LoadImage('pen3.jpg')
    lasttmp, tmpseq = transtemplate(template)

    DEVICE = 0 #/dev/video0
    # create windows
    cv.NamedWindow('Camera')
 

    # create capture device
    device = 0 # assume we want first device
    capture = cv.CreateCameraCapture(DEVICE)
#    cv.ShowImage('pen', lasttmp) 
    k = ''
    while k !='q' :
        frame = cv.QueryFrame(capture)#cv.RetrieveFrame(capture)

        if frame is None:
            break
 
        # mirror
        cv.Flip(frame, None, 1)
        
        # face detection
        cv.ShowImage('Orig', frame)
        frame = detect(frame)
        
        # display webcam image
        cv.ShowImage('Camera', frame)


        # handle events
        k = cv.WaitKey(10)



