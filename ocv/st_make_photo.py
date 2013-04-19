import sys
import cv
import time
import math

if __name__ == "__main__":
    #DEVICE = int(sys.argv[1]) if len(sys.argv) > 1 else 0 #/dev/video0
    cv.NamedWindow('Camera0')
    cv.NamedWindow('Camera1')
    capture0 = cv.CreateCameraCapture(1)
    capture1 = cv.CreateCameraCapture(2)
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
            nm = str(i)
            #if i < 10: nm = '0' + nm
            cv.SaveImage('photos/left%s.jpg' % nm, frame1) # "k" button
            cv.SaveImage('photos/right%s.jpg' % nm, frame0) # "k" button
            i+=1
    print 'saving stereo_calib.xml'
    with open('photos/stereo_calib.xml', 'w') as f:
        f.write('''<?xml version="1.0"?>
        <opencv_storage>
        <imagelist>
        ''')
        for j in xrange(i):
            f.write('"left%s.jpg"\n' % str(j))
            f.write('"right%s.jpg"\n' % str(j))
        f.write('''</imagelist>
        </opencv_storage>''')
    print 'END'
