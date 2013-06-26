import sys
import cv
 
import time

import math

#	cascade = cv.Load('frontalface10/haarcascade_frontalface_alt.xml')

oldscale = None

k = ''
mode = k

def detect(image, oldscale):
    image_size = cv.GetSize(image)
 
    # create grayscale version
    grayscale = image#cv.CreateImage(image_size, 8, 1)
    #dst = cv.CreateImage(image_size, 8, 1)
    #cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    
    #image[10,10] = (0, 255, 0)
    if mode == 1048626:
        oldscale = grayscale
        #print 'fwwffwfw2222'
        
    if mode == 1048625:
        diff = cv.CreateImage(cv.GetSize(grayscale), grayscale.depth, 1)
        diff = cv.CloneImage(grayscale)
        cv.AbsDiff(grayscale, oldscale, diff)
        #cv.Sub(grayscale, oldscale, diff)
        #print '2222'
        dst = cv.CreateImage(image_size, 8, 1)
        cv.CvtColor(diff, dst, cv.CV_BGR2GRAY)
        #cv.EqualizeHist(dst, dst)
        st = time.time()
        for i in xrange(0, image_size[1]):
            for j in xrange(0, image_size[0]):
                if abs(dst[i, j])>0:
                    cv.Circle(image, (i, j), 3, cv.CV_RGB(0,0,255))
        #print time.time() - st
    # create storage
    storage = cv.CreateMemStorage(0)
#    cv.ClearMemStorage(storage)
 
    # equalize histogram
    
    #oldscale = grayscale

    return image, oldscale

if __name__ == "__main__":
 

    DEVICE = 0 #/dev/video0
    # create windows
    cv.NamedWindow('Camera')
 
    # create capture device
    device = 0 # assume we want first device
    capture = cv.CreateCameraCapture(DEVICE)
     
    while k !='q' :
        frame = cv.QueryFrame(capture)#cv.RetrieveFrame(capture)

        if frame is None:
            break
 
        # mirror
        cv.Flip(frame, None, 1)
        
        # face detection
        frame, oldscale = detect(frame, oldscale)
        
        # display webcam image
        cv.ShowImage('Camera', frame)


        # handle events
        k = cv.WaitKey(10)
        if k !=-1 :
            mode = k
            print k


