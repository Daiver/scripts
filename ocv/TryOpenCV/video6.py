import sys

import cv

import numpy as np
 
import time

import math


class videowork:

    def __init__(self):
        self.MAX_COUNT = 1

        self.currentrect = (170, 80, 80, 80)

        self.mode = -1

        self.holded = None

        self.oldgray = None


    def diffX(self, rect, img):
        n = rect[2] * rect[3]
        res = []
        for i in xrange(0, rect[2]):
            for j in xrange(0, rect[3]):
                res.append(img[i + rect[0], j + rect[1]] - img[i + rect[0] - 1, j + rect[1]])
        return res

    
    def diffY(self, rect, img):
        n = rect[2] * rect[3]
        res = []
        for i in xrange(0, rect[2]):
            for j in xrange(0, rect[3]):
                res.append(img[i + rect[0], j + rect[1]] - img[i + rect[0], j + rect[1] -1 ])
        return res


    def difftime(self, rect, img1, img2):
        n = rect[2] * rect[3]
        res = []
        for i in xrange(0, rect[2]):
            for j in xrange(0, rect[3]):
                res.append(img1[i + rect[0], j + rect[1]] - img2[i + rect[0], j + rect[1]])
        return res


    def MkGausFromPoint(self, point, N, M):
        omega = 1.0
        mu = 0

        res = []
        
        f = lambda x: 1/(omega * 2 * math.pi) * math.exp (-(x**2)/2*omega )

        dist = lambda p1, p2: (p1[0] - p2[0])**2 + (p1[1] - p2[1])**2

        for i in xrange(N):
            for j in xrange(M):
                res.append( f(dist(point, (i, j)) ) )
                
        return res

    def work(self, image):

        currentrect = self.currentrect
        
        image_size = cv.GetSize(image)
        
        # create grayscale version
        grayscale = cv.CreateImage(image_size, 8, 1)
        cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
        
        storage = cv.CreateMemStorage(0)
        cv.EqualizeHist(grayscale, grayscale)

        eig = cv.CreateImage (cv.GetSize (grayscale), 32, 1)
        temp = cv.CreateImage ( (cv.GetSize (grayscale)[0] + 1, cv.GetSize (grayscale)[1] + 1), 32, 1)

        # the default parameters
        quality = 0.01
        min_distance = 15
        # search the good points    
        cv.SetImageROI(grayscale, currentrect)
            
        cv.Rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2] + currentrect[0], currentrect[3] + currentrect[1]), (0, 255, 0), 1)
        cv.EllipseBox

        if not self.holded:
            features = cv.GoodFeaturesToTrack (
                grayscale, eig, temp,
                self.MAX_COUNT,
                quality, min_distance, None, 3, 0, 0.04)
        else:
           features = self.holded

        if self.mode == 114:
            self.holded = None
            print 'reset holded'
            self.mode = 0
           
        if self.mode == 104:
            self.holded = features
            print features            
            self.mode = 10

        cv.SetImageROI(image, currentrect)
        
        for (x,y) in features:
            cv.Circle (image, (int(x), int(y)), 3, (0, 255, 0), -1, 8, 0)

        
        cv.ResetImageROI(image)
        cv.ResetImageROI(grayscale)

        if self.mode == 10:

            workpoint = features[0]
            
            timedifference = self.difftime(self.currentrect, self.oldgray, grayscale)
            Xdifference = self.diffX(self.currentrect, grayscale)
            Ydifference = self.diffY(self.currentrect, grayscale)

            W = self.MkGausFromPoint(workpoint, currentrect[2], currentrect[3])

            firstsq = 0
            for i in xrange(0, len(Xdifference)):
                firstsq += W[i] * Xdifference[i]**2

            secondsq = 0
            for i in xrange(0, len(Ydifference)):
                secondsq += W[i] * Ydifference[i]**2

            mixsq = 0
            for i in xrange(0, len(Ydifference)):
                mixsq += W[i] * Ydifference[i] * Xdifference[i]
            
            arr = np.array([firstsq, mixsq, mixsq, secondsq]).reshape(2, 2)

            firstsq = 0
            for i in xrange(0, len(Ydifference)):
                firstsq += W[i] * timedifference[i] * Xdifference[i]
            firstsq = - firstsq

            secondsq = 0
            for i in xrange(0, len(Ydifference)):
                secondsq += W[i] * timedifference[i] * Ydifference[i]
            secondsq = - secondsq

            vect = np.array([firstsq, secondsq]).reshape(2, 1)
            print self.holded[0], 'v'
            self.holded[0] = (vect[0, 0], vect[1, 0])

            #cv.Circle (image, (int(vect[0, 0]), int(vect[1, 0])), 3, (0, 255, 0), -1, 8, 0)
            
            print '\nres',np.dot(arr.T, vect)
            

        self.oldgray = grayscale
        
        return image

    
    def run(self):    

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
            cv.Flip(frame, None, 1)                    
            frame = self.work(frame)            
            # display webcam image
            cv.ShowImage('Camera', frame)
            k = cv.WaitKey(10) % 0x100
            if k !=255 :
                self.mode = k
                print 'pressed', k

if __name__ == "__main__":
    work = videowork()
    work.run()
    
