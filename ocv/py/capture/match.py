import numpy as np
import cv2
from functools import partial

if __name__ == '__main__':
    key = 0
    camCap = cv2.VideoCapture(0)
    while key != 27:
        ret, frame = camCap.read()
        cv2.imshow('', frame)
        key = cv2.waitKey(1) % 0x100
