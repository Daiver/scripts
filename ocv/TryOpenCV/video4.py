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
    
    
    storage = cv.CreateMemStorage(0)
#    cv.ClearMemStorage(storage)
 
    # equalize histogram
    cv.EqualizeHist(grayscale, grayscale)
    st = time.time()
    cv.SetImageROI(image, (100,100,50,50))
    template=cv.CloneImage(image)
    
    cv.ResetImageROI(image)

    cv.ResetImageROI(image)
    W,H=cv.GetSize(image)
    w,h=cv.GetSize(template)
    width=W-w+1
    height=H-h+1
    result=cv.CreateImage((width,height),32,1)
    cv.MatchTemplate(frame,template, result,cv.CV_TM_SQDIFF)
    (min_x,max_y,minloc,maxloc)=cv.MinMaxLoc(result)
    (x,y)=minloc
    cv.Rectangle(image,(int(x),int(y)),(int(x)+w,int(y)+h),(255,255,255),1,0)
    #print time.time() - st
    #cv.SURFParams(500, 1)
    return image


if __name__ == "__main__":
 

    DEVICE = 0 #/dev/video0
    # create windows
    cv.NamedWindow('Camera')
 
    # create capture device
    device = 0 # assume we want first device
    capture = cv.CreateCameraCapture(DEVICE)

    #gray = None
 
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
        k = cv.WaitKey(1)



