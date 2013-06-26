
import sys

import cv

stsize = (40, 25)#size of image for NN
'''
def ToGray(image):
    image_size = cv.GetSize(image)
        
    # create grayscale version
    grayscale = cv.CreateImage(image_size, 8, 1)

    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    
    cv.EqualizeHist(grayscale, grayscale)
    
    return grayscale
'''        

def FeaturesFromImg(image, size):#convert image to list of features for NN    
    newimg = cv.CreateImage(size, image.depth, image.nChannels );
    cv.Resize(image, newimg)
    '''
    image_size = cv.GetSize(newimg)
    grayscale = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(newimg, grayscale, cv.CV_RGB2GRAY)
    '''
    
    res = []

    for i in xrange(0, size[1]):
        for j in xrange(0, size[0]):
            res.append(255 - newimg[i, j])#dark pix is more important            
    return res    


def FeaturesFromFile(fname, size=stsize):

    image = cv.LoadImage(fname, cv.CV_LOAD_IMAGE_GRAYSCALE)
    #image = ToGray(image)
    #image_size = cv.GetSize(image)

    return FeaturesFromImg(image, size)

#cv.ShowImage('img', image)
#print 'press any key'
#cv.WaitKey(100000)

#res = FeaturesFromFile('pos/1.jpg')
#print res
