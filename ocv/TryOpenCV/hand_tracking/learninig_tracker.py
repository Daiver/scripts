import sys

import cv
print 'import cv'

import cv2
print 'import cv2'

import numpy as np
print 'import numpy' 

import time

import math

from Queue import Queue

import pickle

import pybrain
from pybrain.datasets            import ClassificationDataSet
from pybrain.utilities           import percentError
from pybrain.tools.shortcuts     import buildNetwork
from pybrain.supervised.trainers import BackpropTrainer, RPropMinusTrainer
from pybrain.structure.modules   import SoftmaxLayer

from random import random

from imgwork import FeaturesFromFile, FeaturesFromImg

from lkdetector import LKDetector, PatchBoundary
print 'import lkdetector'

def RectToPoints(rect):
    return (rect[0], rect[1]) ,(rect[0] + rect[2], rect[1] + rect[3])

def rangecheck(rect):
            return rect[0] > 0 and rect[1] > 0 and (rect[2] + rect[0]) < 640 and (rect[3] + rect[1]) < 480

def RandomRect(rect):
    rndstep = 200
    res = (int(rect[0] + random() * rndstep - rndstep/2.0 ),
            int(rect[1] + random() * rndstep - rndstep/2.0 ), rect[2], rect[3])
    while not rangecheck(res):
        res = (int(rect[0] + random() * rndstep - rndstep/2.0 ),
            int(rect[1] + random() * rndstep - rndstep/2.0 ), rect[2], rect[3])
    return res


class videowork:

    def __init__(self):
        #self.currentrect = (320, 80, 127, 170)
        self.ninsize = (25, 25)
        self.pt1 = (320, 80)
        self.pt2 = (447, 250)
        self.additionslds = ClassificationDataSet(self.ninsize[0] * self.ninsize[1], nb_classes=2)
        self.key = -1
        self.detector = LKDetector(5, 5)
        f = open('WorkingNNs/l17bak_25_25_1by1', 'r')
        #f = open('___learned3', 'r')
        self.net = pickle.load(f)
        #self.net = buildNetwork(self.ninsize[0] * self.ninsize[1], 96, self.additionslds.outdim, outclass=SoftmaxLayer)
        
        f.close()
        self.stage = 0
        self.numoflearning = 0
        '''
            0 - nothing
            1 - learning with lk
            2 - learning without lk
        '''
        #self.addlflag = False
        #print self.additionslds.outdim
        #exit()

    def ImageFromRect(self, image, rect):        
            
        cv.SetImageROI(image, rect)
        tmp = cv.CreateImage((rect[2], rect[3]), 8, 1)
        cv.Copy(image, tmp)
        cv.ResetImageROI(image)

        return tmp

    def ClassifyImage(self, image):
        features = FeaturesFromImg(image, self.ninsize)
        '''if self.addlflag:
            self.additionslds.addSample(features, [1])'''
        return self.net.activate(features).argmax()

    def ClassifyWindow(self, image, rect):
            
        tmp = self.ImageFromRect(image, rect)
        '''if self.addlflag:
            for i in xrange(2):
                badwin = self.ImageFromRect(image, RandomRect(rect))
                features = FeaturesFromImg(badwin, self.ninsize)
                self.additionslds.addSample(features, [0])
            print 'len of new dataset', len(self.additionslds)
        '''
        return self.ClassifyImage(tmp)

    def SearchObject(self, image, startrect):
        #print cv.GetSize(image), 'SIZE'
        windowstep = 10        
        
        def NewRects(rect, alreadycreated):
            res = []
            res.append((rect[0] + windowstep, rect[1], rect[2], rect[3]))
            res.append((rect[0], rect[1] + windowstep, rect[2], rect[3]))
            res.append((rect[0] - windowstep, rect[1], rect[2], rect[3]))
            res.append((rect[0], rect[1] - windowstep, rect[2], rect[3]))

            res = [x for x in res if (x not in alreadycreated) and rangecheck(x)]

            for x in res:
                alreadycreated[x] = 1
            #print res            
            return res

        searchlimit = 256
        
        alreadycreated = {}

        qu = Queue()
        qu.put(startrect)
        isdetected = False

        res = None
        
        while (not isdetected) and (not qu.empty()) and (searchlimit > 0):
            rect = qu.get()
            searchlimit -= 1
            #print rect
            
            isdetected = self.ClassifyWindow(image, rect)
            #cv.Rectangle(image, (rect[0], rect[1]) ,(rect[0] + rect[2], rect[1] + rect[3]),(255, 255, 0))
            if isdetected:
                res = rect
            else:
                li = NewRects(rect, alreadycreated)
                for x in li: qu.put(x)
                
        return res

    def work(self, image):
        width = self.pt2[0] - self.pt1[0]
        height = self.pt2[1] - self.pt1[1]
        currentrect = (self.pt1[0], self.pt1[1], width, height)#self.currentrect
        #print currentrect
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
            
        
        cv.Rectangle (image, self.pt1, self.pt2, (0, 255, 0), 1)
        
        cv.SetImageROI(image, currentrect)
        
        st = time.time()
        
        out = self.ClassifyWindow(grayscale, currentrect)
        print out, '|time', time.time() - st

        cv.ResetImageROI(image)        

        if out == 1:
            cv.Rectangle (image, (currentrect[0], currentrect[1]), (currentrect[2] + currentrect[0], currentrect[3] + currentrect[1]), (0, 255, 255), 5)

            self.pt1, self.pt2 = PatchBoundary(tracks, self.pt1, self.pt2)
            tmp = self.ImageFromRect(grayscale, currentrect)
            features = FeaturesFromImg(grayscale, self.ninsize)
            self.additionslds.addSample(features, [1])
            for i in xrange(2):
                badwin = self.ImageFromRect(grayscale, RandomRect(currentrect))
                features = FeaturesFromImg(badwin, self.ninsize)
                self.additionslds.addSample(features, [0])
            print 'len of new dataset', len(self.additionslds)
        '''
        else:
            rect = self.SearchObject(grayscale, currentrect)
            if rect:
                self.pt1, self.pt2 = RectToPoints(rect)
        '''

        if self.stage > 0:
            tmp = self.ImageFromRect(grayscale, currentrect)
            features = FeaturesFromImg(grayscale, self.ninsize)
            self.additionslds.addSample(features, [1])
            for i in xrange(2):
                badwin = self.ImageFromRect(grayscale, RandomRect(currentrect))
                features = FeaturesFromImg(badwin, self.ninsize)
                self.additionslds.addSample(features, [0])
            print 'len of new dataset', len(self.additionslds)

        if len(self.additionslds) > 20:
            
            self.additionslds._convertToOneOfMany( )
            self.additionslds.outdim = self.net.outdim
            
            #net = buildNetwork(self.ninsize[0] * self.ninsize[1], 96, self.additionslds.outdim, outclass=SoftmaxLayer)
            trainer = RPropMinusTrainer(
                self.net, dataset=self.additionslds,
                momentum=0.1, verbose=True, weightdecay=0.01)
            '''trainer = BackpropTrainer(
                self.net, dataset=self.additionslds,
                momentum=0.1, verbose=True, weightdecay=0.01)'''
            trainer.trainEpochs( 3 )
            self.additionslds.clear()
            self.numoflearning += 1
        
        if self.key == 113:            
            cv.SaveImage('img.bmp', image)
            self.key = 255

        if self.key == 119:            
            self.stage = 1
            self.key = 255

        if self.stage == 1 and self.numoflearning > 2:
            self.stage = 2

        '''   
        for item in tracks:
            cv.Circle(image, (item[-1][0], item[-1][1]), 2, (0, 255, 0), -1)
        '''
        
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
    print 'load NN'
    
    work.run()
    
'''
    image = cv.LoadImage('img.bmp')
    image_size = cv.GetSize(image)

    # create grayscale version
    grayscale = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    st = time.time()
    rect = work.SearchObject(grayscale, (320, 80, 127, 170))
    print rect, 'time', time.time() - st
    cv.Rectangle(image, (rect[0], rect[1]) ,(rect[0] + rect[2], rect[1] + rect[3]),(255, 0, 0))
    cv.ShowImage('', grayscale)
    cv.ShowImage('2', image)
    cv.WaitKey(1000)
    exit()'''
