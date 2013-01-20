import cv2
import numpy as np
from time import time
import sys
import os

wdir = sys.argv[1]
def surffromimg(img):
    surf = cv2.SURF()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    st = time()
    kp, desc = surf.detect(gray, None, False)
    print 't', time()  - st
    for x in kp:
        cv2.circle(img, (int(x.pt[0]), int(x.pt[1])), 2, (0, 255, 0))
    #cv2.imshow('', img)
    #cv2.waitKey(10000)
    return img, kp, desc
imagesnames = os.listdir(wdir)
imagesnames.sort()
for i, name in enumerate(imagesnames):
    img = cv2.imread(os.path.join(wdir,name))
    img, kp, desc = surffromimg(img)
    #cv2.imshow(name, img)
    cv2.imshow('', img)
    cv2.waitKey()
    if i > 39:break
