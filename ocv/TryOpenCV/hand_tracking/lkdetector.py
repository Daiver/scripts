import cv2

import numpy as np

lk_params = dict( winSize  = (15, 15), 
                  maxLevel = 2, 
                  criteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03),
                  derivLambda = 0.0 )    

feature_params = dict( maxCorners = 500, 
                       qualityLevel = 0.3,
                       minDistance = 7,
                       blockSize = 7 )

class LKDetector:
    def __init__(self, tracklen, detect_interval):
        self.track_len = tracklen
        self.detect_interval = detect_interval
        self.tracks = []
        #self.cam = cv2.VideoCapture(0)#video.create_capture(video_src)
        self.frame_idx = 0

    def detect(self, frame_gray, mask):
        
        if len(self.tracks) > 0:
            img0, img1 = self.prev_gray, frame_gray#old and new image
            p0 = np.float32([tr[-1] for tr in self.tracks]).reshape(-1, 1, 2)#something strange
            p1, st, err = cv2.calcOpticalFlowPyrLK(img0, img1, p0, None, **lk_params)
                
            p0r, st, err = cv2.calcOpticalFlowPyrLK(img1, img0, p1, None, **lk_params)
            d = abs(p0-p0r).reshape(-1, 2).max(-1)#calc error for every point(?)

            good = d < 1#flag(s)
                
            new_tracks = []
            for tr, (x, y), good_flag in zip(self.tracks, p1.reshape(-1, 2), good):#taking old points, new points and flags
                if not good_flag:#if bad error then next
                    continue
                tr.append((x, y))#maybe it is path?
                if len(tr) > self.track_len:#delete old points
                    del tr[0]
                new_tracks.append(tr)#create new list of tracking points
            #cv2.circle(vis, (x, y), 2, (0, 255, 0), -1)#draw it
            self.tracks = new_tracks

        if self.frame_idx % self.detect_interval == 0:
            
                
            for x, y in [np.int32(tr[-1]) for tr in self.tracks]:
                cv2.circle(mask, (x, y), 5, 0, -1)
            p = cv2.goodFeaturesToTrack(frame_gray, mask = mask, **feature_params)
                #print p, '!!!!!!!!!!!'
            if p is not None:
                for x, y in np.float32(p).reshape(-1, 2):
                    self.tracks.append([(x, y)])
            
        self.frame_idx += 1
        self.prev_gray = frame_gray
        return self.tracks

def PatchBoundary(tracks, pt1, pt2):
    s = [0, 0]
    counter = [0, 0]
    for item in tracks:
        if len(item) > 1:
            d = [item[-1][0] - item[-2][0], item[-1][1] - item[-2][1]]
            s[0] += d[0]
            s[1] += d[1]
            if abs(d[0]) > 0.5:
                counter[0] += 1
            if abs(d[1]) > 0.5:
                counter[1] += 1
                
    s[0] = s[0]/counter[0] if counter[0] > 0 else s[0]
    s[1] = s[1]/counter[1] if counter[1] > 0 else s[1]
    #print s, pt1, pt2
    pt1 = (int(pt1[0] + s[0]), int(pt1[1] + s[1]))
    pt2 = (int(pt2[0] + s[0]), int(pt2[1] + s[1]))

    pt1 = [pt1[0], pt1[1]]
    pt2 = [pt2[0], pt2[1]]

    if pt1[0] < 0:
        pt2[0] += abs(pt1[0])
        pt1[0] = 0
        
    if pt1[1] < 0:
        pt2[1] += abs(pt1[1])
        pt1[1] = 0

    if pt2[0] > 640:
        pt1[0] -= abs(640 - pt2[0])
        pt2[0] = 640


    if pt2[1] > 640:
        pt1[1] -= abs(480 - pt2[1])
        pt2[1] = 480
    
    
    return (pt1[0], pt1[1]), (pt2[0], pt2[1])

'''
detector = LKDetector(5, 5)
cam = cv2.VideoCapture(0)

pt1 = (400, 50)
pt2 = (500, 250)

while 1:
    ret, frame = cam.read()

    vis = frame.copy()
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    mask = np.zeros_like(frame_gray)
    mask[pt1[1]:pt2[1], pt1[0]:pt2[0]] = 255
    
    tracks = detector.detect(frame_gray, mask)
    #print tracks[0]
    for item in tracks:
        cv2.circle(vis, (item[-1][0], item[-1][1]), 2, (0, 255, 0), -1)#draw it
    cv2.polylines(vis, [np.int32(tr) for tr in tracks], False, (0, 255, 0))
    cv2.rectangle(vis, pt1, pt2, (255, 255, 0), 5)
    cv2.imshow('lk_track', vis)
    #patch rect
    pt1, pt2 = PatchBoundary(tracks, pt1, pt2)
    ch = cv2.waitKey(1)
    if ch == 27:
        break
'''
