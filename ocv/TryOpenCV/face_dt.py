
import threading

import sys

import cv
 
import time

import math

from random import random

class VideoWork:

    def work(self, frame):
        if self.detectthreadfinish > 0:
            self.detectthreadfinish -= 1
        if not self.detectthread or self.detectthreadfinish == 0:
             self.detectthread = threading.Thread(target=self.detectfaces, args = (frame, ))
             self.detectthreadfinish = -1000
             self.detectthread.start()
        #self.detectfaces(frame)
        self.drawrects(frame, self.faces)
        return frame

    def detectfaces(self, image):
        print '******'
        image_size = cv.GetSize(image)
        grayscale = cv.CreateImage(image_size, 8, 1)
        cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
        storage = cv.CreateMemStorage(0)
        cv.EqualizeHist(grayscale, grayscale)
        st = time.time()
        faces = cv.HaarDetectObjects(image=grayscale, cascade=self.cascade, 
            storage=storage, scale_factor=1.2, 
            min_neighbors=2, flags=cv.CV_HAAR_DO_CANNY_PRUNING)
        self.faces = faces
        print self.faces
        self.detectthreadfinish = 10
        return faces

    def drawrects(self, image, rects):
        ij=0
        font = cv.InitFont(cv.CV_FONT_HERSHEY_DUPLEX, 2, 2)
        if rects:
            for i in rects:
                ij=ij+1
                cv.Rectangle(image, (i[0][0], i[0][1]),
                             (i[0][0]+i[0][2], i[0][1]+i[0][3]),
                             (100*ij, 0, 0), 3, 8, 0)
                cv.PutText(image, "OpenCV forever!", (i[0][0], i[0][1]), font, cv.RGB(255 , 255 , 255))
    def __init__(self):
        self.cascade = cv.Load('frontalface10/haarcascade_frontalface_alt.xml')
        self.key = ''
        self.detectthread = None
        self.detectthreadfinish = True
        #t1 = Thread(target=count)
        self.faces = []

        DEVICE = 0 #/dev/video0
        cv.NamedWindow('Camera')
        self.capture = cv.CreateCameraCapture(DEVICE)        

    def run(self):
        while self.key != 27:
            frame = cv.QueryFrame(self.capture)#cv.RetrieveFrame(capture)
            frame = self.work(frame)
            cv.ShowImage('Camera', frame)
            self.key = cv.WaitKey(10) % 0x100
            if self.key != 255:
                print self.key

work = VideoWork();
work.run()
'''
cascade = cv.Load('frontalface10/haarcascade_frontalface_alt.xml')

def detect(image):
    image_size = cv.GetSize(image)
 
    # create grayscale version
    grayscale = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    #image[10,10] = (0, 255, 0)
    
    # create storage
    storage = cv.CreateMemStorage(0)
    #cv.ClearMemStorage(storage)
 
    # equalize histogram
    cv.EqualizeHist(grayscale, grayscale)
 
    # detect objects
    st = time.time()
    
    faces = cv.HaarDetectObjects(image=grayscale, cascade=cascade, 
        storage=storage, scale_factor=1.2, 
        min_neighbors=2, flags=cv.CV_HAAR_DO_CANNY_PRUNING)
    print 'time: ',time.time()-st
    #faces = [ [ [10,20,1,2] ], [ [60,60,10,50] ] ]

    #print grayscale
    #exit()
    ''''''sum = 0
    for i in xrange(image_size[1]):
        for j in xrange(image_size[0]):
            sum += grayscale[i,j]
    sum /=image_size[1] * image_size[0]for i in xrange(image_size[1]-1):
        for j in xrange(image_size[0]-1):
            if abs(grayscale[i+1,j] - grayscale[i,j])>=70 or abs(grayscale[i,j+1] - grayscale[i,j])>=70:
                if grayscale[i,j]>sum*1.5:
                    cv.Rectangle(image, (j, i),
                         (j+1,i+1),
                         (0, 255, 0), 3, 8, 0)
'''

'''
    if faces:
        print 'face detected!'
        for i in faces:
            print i
            cv.Rectangle(image, (i[0][0], i[0][1]),
                         (i[0][0]+i[0][2], i[0][1]+i[0][3]),
                         (0, 255, 0), 3, 8, 0)
    return image
'''
'''
    if faces:
        print 'face detected!'
        for i in faces:
            cv.Rectangle(image, cv.Point( int(i.x), int(i.y)),
                         cv.Point(int(i.x + i.width), int(i.y + i.height)),
                         cv.RGB(0, 255, 0), 3, 8, 0)
'''
'''
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

'''

