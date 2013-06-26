import sys

import cv

#import pyfann
 
import time

import math


class videowork:

    def __init__(self):
        self.MAX_COUNT = 10

        self.currentrect = (200, 50, 30, 30)

        self.mode = -1


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
        min_distance = 10
        # search the good points    
        cv.SetImageROI(grayscale, (currentrect[0], currentrect[1], 40, 40))
            
        cv.Rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2], currentrect[3]), (0, 255, 0), 1)

        features = cv.GoodFeaturesToTrack (
            grayscale, eig, temp,
            self.MAX_COUNT,
            quality, min_distance, None, 3, 0, 0.04)

        cv.SetImageROI(image, (currentrect[0], currentrect[1], 50, 50))
        
        for (x,y) in features:
            cv.Circle (image, (int(x), int(y)), 3, (0, 255, 0), -1, 8, 0)

        
        cv.ResetImageROI(image)

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
    
