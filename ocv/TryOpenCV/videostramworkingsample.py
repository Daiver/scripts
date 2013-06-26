import sys
import cv
import time
import math

def work(image):
    image_size = cv.GetSize(image)
    grayscale = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    storage = cv.CreateMemStorage(0)
    cv.EqualizeHist(grayscale, grayscale)
    return image

if __name__ == "__main__":
    DEVICE = 0 #/dev/video0
    cv.NamedWindow('Camera')
    capture = cv.CreateCameraCapture(DEVICE)
    k = ''
    while k != 27 :
        frame = cv.QueryFrame(capture)#cv.RetrieveFrame(capture)

        if frame is None:
            break
 
        # mirror
        cv.Flip(frame, None, 1)
        # face detection
        frame = work(frame)
        # display webcam image
        cv.ShowImage('Camera', frame)
        # handle events
        k = cv.WaitKey(10) % 0x100
        if k == 107:cv.SaveImage('shot.jpg', frame)
