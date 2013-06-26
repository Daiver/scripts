import sys

import cv

import numpy as np
 
import time

import math

import cv2

lk_params = dict( winSize  = (15, 15), 
                  maxLevel = 2, 
                  criteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03),
                  derivLambda = 0.0 )    

feature_params = dict( maxCorners = 500, 
                       qualityLevel = 0.3,
                       minDistance = 7,
                       blockSize = 7 )


class videowork:

    def __init__(self):

        self.currentrect = (170, 80, 80, 80)
        self.track_len = 10
        self.detect_interval = 5
        self.tracks = []
        self.frame_idx = 0

    def work(self, image):

        currentrect = self.currentrect
        
        image_size = cv.GetSize(image)
        # create grayscale version
        frame_gray = cv.CreateImage(image_size, 8, 1)
        cv.CvtColor(image, frame_gray, cv.CV_BGR2GRAY)
        #frame_gray = cv2.cvtColor(frame_gray, cv2.COLOR_BGR2GRAY)
        
        storage = cv.CreateMemStorage(0)
        #cv.EqualizeHist(grayscale, grayscale)

        #vis = grayscale.copy()
        vis = cv.CreateImage(cv.GetSize(image), 8, 3)
        cv.Copy(image, vis)
        #frame_gray = grayscale
        if len(self.tracks) > 0:
            img0, img1 = self.prev_gray, frame_gray
            p0 = np.float32([tr[-1] for tr in self.tracks]).reshape(-1, 1, 2)
            p1, st, err = cv2.calcOpticalFlowPyrLK(img0, img1, p0, None, **lk_params)
            p0r, st, err = cv2.calcOpticalFlowPyrLK(img1, img0, p1, None, **lk_params)
            d = abs(p0-p0r).reshape(-1, 2).max(-1)
            good = d < 1
            new_tracks = []
            for tr, (x, y), good_flag in zip(self.tracks, p1.reshape(-1, 2), good):
                if not good_flag:
                    continue
                tr.append((x, y))
                if len(tr) > self.track_len:
                    del tr[0]
                new_tracks.append(tr)
                cv2.circle(vis, (x, y), 2, (0, 255, 0), -1)
            self.tracks = new_tracks
            cv2.polylines(vis, [np.int32(tr) for tr in self.tracks], False, (0, 255, 0))
            draw_str(vis, (20, 20), 'track count: %d' % len(self.tracks))

        if self.frame_idx % self.detect_interval == 0:
            mask = np.zeros(cv.GetSize(frame_gray))#np.zeros_like(frame_gray)
            #print frame_gray
            #print mask
            mask[:] = 255
            for x, y in [np.int32(tr[-1]) for tr in self.tracks]:
                cv2.circle(mask, (x, y), 5, 0, -1)
            p = cv2.goodFeaturesToTrack(frame_gray, mask = mask, **feature_params)
            if p is not None:
                for x, y in np.float32(p).reshape(-1, 2):
                    self.tracks.append([(x, y)])


        self.frame_idx += 1
        self.prev_gray = frame_gray
        #cv2.imshow('lk_track', vis)
        return vis
    def run(self):    

        DEVICE = 0 #/dev/video0
        # create windows
        cv.NamedWindow('Camera')
     
        # create capture device
        device = 0 # assume we want first device
        capture = cv2.VideoCapture(DEVICE)#cv.CreateCameraCapture(DEVICE)
     
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
    
