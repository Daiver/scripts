import cv 
 
color_tracker_window = "Color Tracker" 
 
class ColorTracker: 
    
    def __init__(self): 
        cv.NamedWindow( color_tracker_window, 1 ) 
        self.capture = cv.CaptureFromCAM(0) 
        
    def run(self): 
        while True: 
            img = cv.QueryFrame( self.capture )                     
            cv.Smooth(img, img, cv.CV_BLUR, 3); 
            
            #convert the image to hsv(Hue, Saturation, Value) so its  
            #easier to determine the color to track(hue) 
            hsv_img = cv.CreateImage(cv.GetSize(img), 8, 3) 
            cv.CvtColor(img, hsv_img, cv.CV_BGR2HSV) 
            
            #limit all pixels that don't match our criteria, in this case we are  
            #looking for purple but if you want you can adjust the first value in  
            #both turples which is the hue range(120,140).  OpenCV uses 0-180 as  
            #a hue range for the HSV color model 
            thresholded_img =  cv.CreateImage(cv.GetSize(hsv_img), 8, 1) 
            cv.InRangeS(hsv_img, (120, 80, 80), (140, 255, 255), thresholded_img) 
            
            #determine the objects moments and check that the area is large  
            #enough to be our object 
            #moments = cv.Moments(thresholded_img, 0)
            moments = cv.Moments(cv.GetMat(thresholded_img,1), 0)

            area = cv.GetCentralMoment(moments, 0, 0) 
            

            if(area > 10000): 

                x = int(cv.GetSpatialMoment(moments, 1, 0)//area )
                y = int(cv.GetSpatialMoment(moments, 0, 1)//area )

                cv.Circle(img, (x, y), 30, cv.CV_RGB(255, 100, 0), 1)

            cv.ShowImage(color_tracker_window, img) 
            
            if cv.WaitKey(10) == 27: 
                break 
                
if __name__=="__main__": 
    color_tracker = ColorTracker() 
    color_tracker.run() 
