import cv

def GetInput(fname, size):
    image = cv.LoadImage(fname)
    newimg = cv.CreateImage(size, image.depth, image.nChannels );
    cv.Resize(image, newimg)
    image_size = cv.GetSize(newimg)
    grayscale = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(newimg, grayscale, cv.CV_RGB2GRAY)

    res = []

    for i in xrange(0, size[0]):
        for j in xrange(0, size[1]):
            res.append( grayscale[i, j])
    return res    
