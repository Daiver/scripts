import sys

import cv

import cv2

import numpy as np
 
import time

import math

import pickle

import Image

from imgwork import FeaturesFromFile, FeaturesFromImg

class videowork:

    def __init__(self):
        self.currentrect = (120, 80, 237, 250)

        self.key = -1

        #f = open('___learned3', 'r')
        f = open('lbaks/l7bak', 'r')
        self.net = pickle.load(f)
        self.ninsize = (50, 80)
        f.close()

    def work(self, image):

        currentrect = self.currentrect

        grayscale = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        cv2.rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2], currentrect[3]), (0, 255, 0), 1)
        
        tmp = grayscale.copy()[
            currentrect[1]:currentrect[3],
            currentrect[0]:currentrect[2]
            ]
        tmp = cv2.resize(tmp, self.ninsize)
        res = []
        #cv2.waitKey(1000)
        #print tmp.shape
        for i in xrange(0, tmp.shape[0]):
            for j in xrange(0, tmp.shape[1]):
                res.append(255 - tmp[i, j])
        st = time.time()
        #tmp = np.array(res).reshape(self.ninsize)
        cv2.imshow('1', tmp)
        out = self.net.activate(res).argmax()
        print out, '|time', time.time() - st
        

        if out == 1:
            cv2.rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2], currentrect[3]), (255, 255, 0), 5)
            exit()

        if self.key == 113:            
            cv.SaveImage('img.bmp', tmp)
            self.key = 255
            cv.Rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2] + currentrect[0], currentrect[3] + currentrect[1]), (0, 255, 255), 1)
                
        

        return image
    def run(self):    

        DEVICE = 0 #/dev/video0
        # create windows
        cv.NamedWindow('Camera')
     
        # create capture device
        device = 0 # assume we want first device
        #capture = cv.CreateCameraCapture(DEVICE)
        cam = cv2.VideoCapture(0)
     
        k = ''
        while k !='q' :
            ret, frame = cam.read()#cv.QueryFrame(capture)#cv.RetrieveFrame(capture)
            if frame is None:
                break    
            #cv.Flip(frame, None, 1)                    
            frame = self.work(frame)            
            # display webcam image
            cv2.imshow('Camera', frame)
            k = cv.WaitKey(10) % 0x100
            if k !=255 :
                self.key = k
                print 'pressed', k

def PIL2array(img):
    return np.array(img.getdata(),
                    np.uint8).reshape(img.size[1], img.size[0], 3)

def array2PIL(arr, size):
    mode = 'RGBA'
    arr = arr.reshape(arr.shape[0]*arr.shape[1], arr.shape[2])
    if len(arr[0]) == 3:
        arr = np.c_[arr, 255*np.ones((len(arr),1), np.uint8)]
    return Image.frombuffer(mode, size, arr.tostring(), 'raw', mode, 0, 1)


if __name__ == "__main__":
    work = videowork()
    
    tmp = cv2.imread('img.bmp', 0)
    img2 = cv.LoadImage('img.bmp', cv.CV_LOAD_IMAGE_GRAYSCALE)
    cv2.imshow('', np.asarray(img2[:,:]))
    cv2.waitKey(1000)
    '''
    res = []
    tmp = cv2.resize(tmp, work.ninsize)
    for i in xrange(0, tmp.shape[0]):
        for j in xrange(0, tmp.shape[1]):
            res.append(255 - tmp[i, j])#dark pix is more important
            #tmp[j, i] = 255 - tmp[j, i]
    
    res2 = FeaturesFromImg(img2, work.ninsize)
    print work.net.activate(res).argmax()
    print work.net.activate(res2).argmax()
    print len(res), len(res2)
    for i in xrange(len(res)):
        print res[i] - res2[i]
        if res[i] != res2[i]:
            print 'yeah'
    '''
    #print img
    #work.run()
    
