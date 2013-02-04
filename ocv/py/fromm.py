from PIL import Image
import glob, os
import cv
import cv2

import numpy as np

cv.NamedWindow("camera", 1)
capture = cv.CaptureFromCAM(0)
 
tmp = cv2.imread('1.jpg')#Image.open("1.jpg")
 
while True:
    img = cv.QueryFrame(capture)
    #print(type(img), type(tmp))
    img = tmp
    result = np.zeros(img.shape)#[[]]
    cv2.matchTemplate(img, tmp,  cv2.TM_CCOEFF_NORMED, result)
    print result
    cv2.imshow("camera", result)
    cv2.waitKey()
    break
cv.DestroyWindow("camera")
