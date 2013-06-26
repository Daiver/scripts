import cv2
import numpy as np
 
img = cv2.imread('img/2.jpg')

h = np.zeros((300,256,3))
 
bins = np.arange(256).reshape(256,1)
#color = [ (255,0,0),(0,255,0),(0,0,255) ]
color = [ (255,255,255),(255,255,255),(255,255,255) ]
pts = []
for ch, col in enumerate(color):
    hist_item = cv2.calcHist([img],[ch],None,[256],[0,255])
    cv2.normalize(hist_item,hist_item,0,255,cv2.NORM_MINMAX)
    hist=np.int32(np.around(hist_item))
    pts = np.column_stack((bins,hist))
    pt1 = (pts[0, 0], pts[0, 1])
    for i in xrange(1, pts.shape[0]):
        pt2 = (pts[i, 0], pts[i, 1])
        cv2.line(h, pt1, pt2, col)
        pt1 = pt2

h=np.flipud(h)

cv2.imshow('colorhist',h)
cv2.waitKey(1000)
