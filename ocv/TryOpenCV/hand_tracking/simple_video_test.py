import sys

import cv

import cv2
from cv2 import SURF

import numpy as np
 
import time

import math

import pickle

from imgwork import FeaturesFromFile, FeaturesFromImg

class videowork:

    def __init__(self):
        self.currentrect = (320, 80, 127, 170)

        self.key = -1

        f = open('WorkingNNs/l16bak_25_25_posp', 'r')#
        self.net = pickle.load(f)
        self.ninsize = (25, 25)
        f.close()

    def work(self, image):

        currentrect = self.currentrect
        
        image_size = cv.GetSize(image)

        # create grayscale version
        grayscale = cv.CreateImage(image_size, 8, 1)
        cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
        
        storage = cv.CreateMemStorage(0)
        cv.EqualizeHist(grayscale, grayscale)

        cv.SetImageROI(grayscale, currentrect)
            
        cv.Rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2] + currentrect[0], currentrect[3] + currentrect[1]), (0, 255, 0), 1)
        
        cv.SetImageROI(image, currentrect)

        tmp = cv.CreateImage((currentrect[2], currentrect[3]), 8, 1)
        cv.Copy(grayscale, tmp)
        
        st = time.time()
        out = self.net.activate(FeaturesFromImg(tmp, self.ninsize)).argmax()
        print out, '|time', time.time() - st

        cv.ResetImageROI(image)
        cv.ResetImageROI(grayscale)

        if out == 1:
            cv.Rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2] + currentrect[0], currentrect[3] + currentrect[1]), (0, 255, 255), 5)

        if self.key == 113:      
            cv.SetImageROI(image, currentrect)      
            cv.SaveImage('img.bmp', image)
            cv.ResetImageROI(image)
            self.key = 255
            cv.Rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2] + currentrect[0], currentrect[3] + currentrect[1]), (0, 255, 255), 1)
                
        

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
                self.key = k
                print 'pressed', k

if __name__ == "__main__":
    work = videowork()
    work.run()
    
