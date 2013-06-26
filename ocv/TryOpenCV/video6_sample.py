import sys

import cv

import numpy as np
 
import time

import math


class videowork:

    def __init__(self):
        self.MAX_COUNT = 3

        self.currentrect = (170, 80, 80, 80)

        self.mode = -1

        self.holded = None


    def work(self, image):

        currentrect = self.currentrect
        
        image_size = cv.GetSize(image)
        global startsum
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


        if not self.holded:
            features = cv.GoodFeaturesToTrack (
                grayscale, eig, temp,
                self.MAX_COUNT,
                quality, min_distance, None, 3, 0, 0.04)
        else:
           features = self.holded
           
        if self.mode == 104:
            self.holded = features
            print features
            self.mode = 0

        cv.SetImageROI(image, currentrect)
        print features
        for (x,y) in features:
            cv.Circle (image, (int(x), int(y)), 3, (0, 255, 0), -1, 8, 0)

        
        cv.ResetImageROI(image)
        cv.ResetImageROI(grayscale)

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
    
