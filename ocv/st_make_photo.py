import sys
import cv
import time
import math

if __name__ == "__main__":
    #DEVICE = int(sys.argv[1]) if len(sys.argv) > 1 else 0 #/dev/video0
    cv.NamedWindow('Camera0')
    cv.NamedWindow('Camera1')
    capture0 = cv.CreateCameraCapture(0)
    capture1 = cv.CreateCameraCapture(1)
    k = ''
    i = 0
    while k != 27 :
        frame0 = cv.QueryFrame(capture0)#cv.RetrieveFrame(capture)
        frame1 = cv.QueryFrame(capture1)#cv.RetrieveFrame(capture)

        if frame1 is None or frame0 is None:
            break
 
        # mirror
        #cv.Flip(frame, None, 1)
        # face detection
        #frame = work(frame)
        # display webcam image
        cv.ShowImage('Camera0', frame0)
        cv.ShowImage('Camera1', frame1)
        # handle events
        k = cv.WaitKey(10) % 0x100
        if k == 107:
            cv.SaveImage('photos/left%s.jpg' % str(i), frame1) # "k" button
            cv.SaveImage('photos/right%s.jpg' % str(i), frame0) # "k" button
            i+=1
