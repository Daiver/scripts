import sys
import cv
 
import time

import math

cascade = cv.Load('frontalface10/haarcascade_frontalface_alt.xml')

def detect(image):
    image_size = cv.GetSize(image)
 
    # create grayscale version
    grayscale = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    #image[10,10] = (0, 255, 0)
    
    # create storage
    storage = cv.CreateMemStorage(0)
    #cv.ClearMemStorage(storage)
 
    # equalize histogram
    cv.EqualizeHist(grayscale, grayscale)
 
    # detect objects
    st = time.time()
    
    faces = cv.HaarDetectObjects(image=grayscale, cascade=cascade, 
        storage=storage, scale_factor=1.2, 
        min_neighbors=2, flags=cv.CV_HAAR_DO_CANNY_PRUNING)
    print 'time: ',time.time()-st
    #faces = [ [ [10,20,1,2] ], [ [60,60,10,50] ] ]

    #print grayscale
    #exit()
    '''sum = 0
    for i in xrange(image_size[1]):
        for j in xrange(image_size[0]):
            sum += grayscale[i,j]
    sum /=image_size[1] * image_size[0]'''
    '''for i in xrange(image_size[1]-1):
        for j in xrange(image_size[0]-1):
            if abs(grayscale[i+1,j] - grayscale[i,j])>=70 or abs(grayscale[i,j+1] - grayscale[i,j])>=70:
                if grayscale[i,j]>sum*1.5:
                    cv.Rectangle(image, (j, i),
                         (j+1,i+1),
                         (0, 255, 0), 3, 8, 0)
'''


    if faces:
        print 'face detected!'
        for i in faces:
            print i
            cv.Rectangle(image, (i[0][0], i[0][1]),
                         (i[0][0]+i[0][2], i[0][1]+i[0][3]),
                         (0, 255, 0), 3, 8, 0)
    return image

'''
    if faces:
        print 'face detected!'
        for i in faces:
            cv.Rectangle(image, cv.Point( int(i.x), int(i.y)),
                         cv.Point(int(i.x + i.width), int(i.y + i.height)),
                         cv.RGB(0, 255, 0), 3, 8, 0)
'''
if __name__ == "__main__":
 

    DEVICE = 0 #/dev/video0
    # create windows
    cv.NamedWindow('Camera')
 
    # create capture device
    device = 0 # assume we want first device
    capture = cv.CreateCameraCapture(DEVICE)
 
    k = ''
    while k !='q' :
        frame = cv.QueryFrame(capture)#cv.RetrieveFrame(capture)

        if frame is None:
            break
 
        # mirror
        cv.Flip(frame, None, 1)
        
        # face detection
        frame = detect(frame)
        
        # display webcam image
        cv.ShowImage('Camera', frame)


        # handle events
        k = cv.WaitKey(10)



