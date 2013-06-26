#!/usr/bin/env python

import cv

from ctypes import cdll

DEV = 0

class Target:

    def __init__(self, devicenum):
        self.capture = cv.CaptureFromCAM(devicenum)
        self.mode = 255
        self.workrect = (0, 0, 100, 200)
        cv.NamedWindow("Target", 1)

 
    def move_mouse(self, x,y):
      dll = cdll.LoadLibrary('libX11.so')
      d = dll.XOpenDisplay(None)
      root = dll.XDefaultRootWindow(d)
      dll.XWarpPointer(d,None,root,0,0,0,0,x,y)
      dll.XCloseDisplay(d)

    def run(self):
        # Capture first frame to get size
        frame = cv.QueryFrame(self.capture)
        frame_size = cv.GetSize(frame)
        color_image = cv.CreateImage(cv.GetSize(frame), 8, 3)
        grey_image = cv.CreateImage(cv.GetSize(frame), cv.IPL_DEPTH_8U, 1)
        moving_average = cv.CreateImage(cv.GetSize(frame), cv.IPL_DEPTH_32F, 3)

        first = True

        while True:
            closest_to_left = cv.GetSize(frame)[0]
            closest_to_right = cv.GetSize(frame)[1]

            color_image = cv.QueryFrame(self.capture)

            # Smooth to get rid of false positives
            cv.Smooth(color_image, color_image, cv.CV_GAUSSIAN, 3, 0)

            if first:
                difference = cv.CloneImage(color_image)
                temp = cv.CloneImage(color_image)
                cv.ConvertScale(color_image, moving_average, 1.0, 0.0)
                first = False
            else:
                cv.RunningAvg(color_image, moving_average, 0.020, None)

            # Convert the scale of the moving average.
            cv.ConvertScale(moving_average, temp, 1.0, 0.0)

            # Minus the current frame from the moving average.
            cv.AbsDiff(color_image, temp, difference)

            # Convert the image to grayscale.
            cv.CvtColor(difference, grey_image, cv.CV_RGB2GRAY)
            cv.SetImageROI(grey_image, self.workrect)
            # Convert the image to black and white.
            cv.Threshold(grey_image, grey_image, 40, 255, cv.CV_THRESH_BINARY)

            # Dilate and erode to get people blobs
            cv.Dilate(grey_image, grey_image, None, 18)
            cv.Erode(grey_image, grey_image, None, 10)

            storage = cv.CreateMemStorage(0)
            contour = cv.FindContours(grey_image, storage, cv.CV_RETR_CCOMP, cv.CV_CHAIN_APPROX_SIMPLE)
            points = []
            cv.ResetImageROI(grey_image)
            while contour:
                bound_rect = cv.BoundingRect(list(contour))
                contour = contour.h_next()

                pt1 = (bound_rect[0], bound_rect[1])
                pt2 = (bound_rect[0] + bound_rect[2], bound_rect[1] + bound_rect[3])
                points.append(pt1)
                points.append(pt2)
                cv.Rectangle(color_image, pt1, pt2, cv.CV_RGB(255,0,0), 1)

            if len(points):
                center_point = reduce(lambda a, b: ((a[0] + b[0]) / 2, (a[1] + b[1]) / 2), points)
                #cv.Circle(color_image, center_point, 40, cv.CV_RGB(255, 255, 255), 1)
                cv.Circle(color_image, center_point, 30, cv.CV_RGB(255, 100, 0), 1)
                cv.Circle(color_image, center_point, 20, cv.CV_RGB(255, 255, 255), 1)
                cv.Circle(color_image, center_point, 10, cv.CV_RGB(255, 100, 0), 1)
                
                if self.mode == 227:
                    self.move_mouse(center_point[0], center_point[1])
            
            cv.ShowImage("Target", color_image)

            
            # Listen for ESC key
            c = cv.WaitKey(7) % 0x100
            if c == 27:
                break
            else:
                if c != 255:
                    self.mode = c
                    print c

if __name__=="__main__":
    t = Target(DEV)
    t.run()
