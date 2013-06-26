
import cv2

import numpy as np

from time import time

import sys

img = cv2.imread(sys.argv[1])#cv2.imread('../../carplate/img/numbers/1.jpg')#cam.read()
def surffromimg(img):
    surf = cv2.SURF()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    st = time()
    kp, desc = surf.detect(gray, None, False)
    print 't', time()  - st
    for x in kp:
        cv2.circle(img, (int(x.pt[0]), int(x.pt[1])), 2, (0, 255, 0))
    cv2.imshow('', img)
    cv2.waitKey(10000)
    return kp, desc

surffromimg(img)
