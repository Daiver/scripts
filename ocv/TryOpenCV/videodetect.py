import sys
import cv
 
import time

cascade = cv.Load('frontalface10/haarcascade_frontalface_alt.xml')
counter = 0

faces = []

def detect(image, faces):
    image_size = cv.GetSize(image)
 
    # create grayscale version
    grayscale = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
 
    # create storage
    storage = cv.CreateMemStorage(0)
#    cv.ClearMemStorage(storage)
 
    # equalize histogram
    cv.EqualizeHist(grayscale, grayscale)
 
    # detect objects
#    st = time.time()
#    if counter % 10 == 0:    
    faces = cv.HaarDetectObjects(image=grayscale, cascade=cascade, 
            storage=storage, scale_factor=1.2, 
            min_neighbors=2, flags=cv.CV_HAAR_DO_CANNY_PRUNING)
#    print 'time: ',time.time()-st
    if faces:
#        print 'face detected!'
        for i in faces:
#            
            cv.Rectangle(image, (i[0][0], i[0][1]),
                             (i[0][0]+i[0][2], i[0][1]+i[0][3]),
                             (0, 255, 0), 3, 8, 0)

'''
    if faces:
        print 'face detected!'
        for i in faces:
            cv.Rectangle(image, cv.Point( int(i.x), int(i.y)),
                         cv.Point(int(i.x + i.width), int(i.y + i.height)),
                         cv.RGB(0, 255, 0), 3, 8, 0)
'''
if __name__ == "__main__":
 
    print "Press ESC to exit ..."
 
    # create windows
    cv.NamedWindow('Camera')
 
    # create capture device
    device = 0 # assume we want first device
    capture = cv.CreateCameraCapture(0)
#    cv.SetCaptureProperty(capture, cv.CAP_PROP_FRAME_WIDTH, 640)
#    cv.SetCaptureProperty(capture, cv.CAP_PROP_FRAME_HEIGHT, 480)    
 
    # check if capture device is OK
    if not capture:
        print "Error opening capture device"
        sys.exit(1)
    k = ''

    #acts = [ detect, lambda x:x ]
    while k !='q' :
        counter += 1
        # do forever
	#        st = time.time() 
        # capture the current frame
        frame = cv.QueryFrame(capture)
#        print 't:', time.time() - st
        if frame is None:
            break
 
        # mirror
        cv.Flip(frame, None, 1)
        
        # face detection
        #detect(frame)
#        if counter % 10 ==0:
        detect(frame, faces)        

        # display webcam image
        cv.ShowImage('Camera', frame)


        # handle events
        k = cv.WaitKey(5)
 
        if k == 0x1b: # ESC
            print 'ESC pressed. Exiting ...'
            break
