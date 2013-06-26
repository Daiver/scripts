import cv2
import numpy as np
 
img = cv2.imread('img/4.jpg')

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

print img.shape

h = np.zeros((256, img.shape[1], 3))

W = []
for i in xrange(gray.shape[1]):
    w = sum(gray[:,i]) / float(gray.shape[0])
    W.append(w)
    #print i

pt0 = None
pt1 = None

avgw = sum(W) / len(W)
print avgw
#W = [x/avgw for x in W]
#print W
for i, w in enumerate(W):
    if w >= 235:
        cv2.line(img, (i, 0), (i, 1000), (255, 0, 0))
    if not pt1:
        pt1 = (i, int(w))
    else:
        pt2 = (i, int(w))
        cv2.line(h, pt1, pt2, (255, 255, 255))
        pt0 = pt1
        pt1 = pt2

cv2.imshow('c', img)
cv2.imshow('colorhist',h)
cv2.imwrite('1.jpg', h)
cv2.waitKey(1000)

'''
        if pt0:
            if (pt0[1] < pt1[1]) and (pt2[1] < pt1[1]) or (pt0[1] > pt1[1]) and (pt2[1] > pt1[1]):
                cv2.line(img, (i, 0), (i, 1000), (255, 0, 0))
                cv2.line(h, (i, 0), (i, 1000), (255, 0, 0))

'''

'''
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
'''
