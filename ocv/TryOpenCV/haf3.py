import sys
import cv
 
import time

import math

#	cascade = cv.Load('frontalface10/haarcascade_frontalface_alt.xml')

def detect(image):
    image_size = cv.GetSize(image)
 
    # create grayscale version
    grayscale = cv.CreateImage(image_size, 8, 1)
    #dst = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    #image[10,10] = (0, 255, 0)
    
    # create storage
    storage = cv.CreateMemStorage(0)
    #cv.ClearMemStorage(storage)
 
    # equalize histogram
    cv.EqualizeHist(grayscale, grayscale)

#    cv.Canny(grayscale, dst, 60, 200, 3)#!!!!!
    #cv.Canny(grayscale, dst, 40, 200, 3)
    #st = time.time()
    cv.Smooth(image, image, cv.CV_GAUSSIAN, 5, 5 );
    cstr = cv.CreateMat(10, 1, 1)
    results = cv.HoughCircles( 
                grayscale, 
                cstr, 
                cv.CV_HOUGH_GRADIENT, 
                10,
                60.0
                
                )
    #lines = cv.HoughLines2( dst, storage, cv.CV_HOUGH_PROBABILISTIC, 1, cv.CV_PI/180, 50, 50, 10 )
    #for line in lines:
    #    cv.Line(image, line[0], line[1], cv.CV_RGB(255,0,0), 3, cv.CV_AA, 0 )
    #    if abs(line[0][0]-line[1][0])<5:
    #        cv.Line(image, line[0], line[1], cv.CV_RGB(0,255,0), 3, cv.CV_AA, 0 )


#    cv.Sub(grayscale, dst, dst)
    #print time.time() - st
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
        frame = detect(frame)
        
        # display webcam image
        cv.ShowImage('Camera', frame)


        # handle events
        k = cv.WaitKey(10)



