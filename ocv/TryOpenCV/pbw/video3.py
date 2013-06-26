import sys

import cv

import cv2

import numpy as np
 
import time

import math

import pickle

from imgwork import FeaturesFromFile, FeaturesFromImg

from lkdetector import LKDetector, PatchBoundary

class videowork:

    def __init__(self):
        #self.currentrect = (320, 80, 127, 170)
        self.pt1 = (320, 80)
        self.pt2 = (447, 250)
        
        self.key = -1
        self.detector = LKDetector(5, 5)
        f = open('___learned3', 'r')
        self.net = pickle.load(f)
        self.ninsize = (80, 50)
        f.close()

    def work(self, image):
        width = self.pt2[0] - self.pt1[0]
        height = self.pt2[1] - self.pt1[1]
        currentrect = (self.pt1[0], self.pt1[1], width, height)#self.currentrect
        print currentrect
        image_size = cv.GetSize(image)

        # create grayscale version
        grayscale = cv.CreateImage(image_size, 8, 1)
        cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
        
        storage = cv.CreateMemStorage(0)
        cv.EqualizeHist(grayscale, grayscale)

        frame = np.asarray(image[:, :])
        
        frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        mask = np.zeros_like(frame_gray)
        mask[self.pt1[1]:self.pt2[1], self.pt1[0]:self.pt2[0]] = 255

        st = time.time()
        tracks = self.detector.detect(frame_gray, mask)
        print 'detect time', time.time() - st
        

        cv.SetImageROI(grayscale, currentrect)
            
        cv.Rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2] + currentrect[0], currentrect[3] + currentrect[1]), (0, 255, 0), 1)
        
        cv.SetImageROI(image, currentrect)

        tmp = cv.CreateImage((currentrect[2], currentrect[3]), 8, 1)
        cv.Copy(grayscale, tmp)
                
        #print len(tracks)
            
        st = time.time()
        out = self.net.activate(FeaturesFromImg(tmp, self.ninsize)).argmax()
        print out, '|time', time.time() - st

        cv.ResetImageROI(image)
        cv.ResetImageROI(grayscale)

        if out == 1:
            cv.Rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2] + currentrect[0], currentrect[3] + currentrect[1]), (0, 255, 255), 5)
            self.pt1, self.pt2 = PatchBoundary(tracks, self.pt1, self.pt2)

        if self.key == 113:            
            cv.SaveImage('img.bmp', tmp)
            self.key = 255
            cv.Rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2] + currentrect[0], currentrect[3] + currentrect[1]), (0, 255, 255), 1)
        for item in tracks:
            cv.Circle(image, (item[-1][0], item[-1][1]), 2, (0, 255, 0), -1)
        #pt1 = (400, 50)
        #pt2 = (500, 250)

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
    
