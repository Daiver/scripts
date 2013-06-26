import cv

def ToGray(image):
    image_size = cv.GetSize(image)
        
    # create grayscale version
    grayscale = cv.CreateImage(image_size, 8, 1)

    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    
    cv.EqualizeHist(grayscale, grayscale)
    
    return grayscale
        
