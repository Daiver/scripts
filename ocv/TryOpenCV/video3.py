import sys
import cv
 
import time

import math

MAX_COUNT = 100

def work(image):
    image_size = cv.GetSize(image)
 
    # create grayscale version
    grayscale = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    #image[10,10] = (0, 255, 0)
    
    # create storage
    storage = cv.CreateMemStorage(0)
#    cv.ClearMemStorage(storage)
 
    # equalize histogram
    cv.EqualizeHist(grayscale, grayscale)

    eig = cv.CreateImage (cv.GetSize (grayscale), 32, 1)
    temp = cv.CreateImage (cv.GetSize (grayscale), 32, 1)
    # the default parameters
    quality = 0.01
    min_distance = 10
    # search the good points    
    
    features = cv.GoodFeaturesToTrack (
    grayscale, eig, temp,
    MAX_COUNT,
    quality, min_distance, None, 3, 0, 0.04)
    for (x,y) in features:
        #print "Good feature a: ", x, ',' ,y
        cv.Circle (image, (int(x), int(y)), 3, (0, 255, 0), -1, 8, 0)

    return image


if __name__ == "__main__":
 

    DEVICE = 0 #/dev/video0
    # create windows
    cv.NamedWindow('Camera')
 
    # create capture device
    device = 0 # assume we want first device
    capture = cv.CreateCameraCapture(DEVICE)
 
    k = ''
    while k !='q' :
        frame = cv.QueryFrame(capture)#cv.RetrieveFrame(capture)

        if frame is None:
            break
 
        # mirror
        cv.Flip(frame, None, 1)
        
        # face detection
        frame = work(frame)
        
        # display webcam image
        cv.ShowImage('Camera', frame)


        # handle events
        k = cv.WaitKey(10)



