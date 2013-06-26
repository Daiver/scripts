import cv

def CurveInvertImg(image):
    image_size = cv.GetSize(image)
    grayscale = cv.CreateImage(image_size, 8, 1)

    cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
    cv.EqualizeHist(grayscale, grayscale)

    cv.Threshold(grayscale, grayscale, 5, 255, cv.CV_THRESH_BINARY)

    cv.Erode(grayscale, grayscale, None, 1)

    dst = cv.CreateImage(image_size, 8, 1)
    cv.Canny(grayscale, dst, 120, 255, 3)
    return dst

def CutFromImage(image, p1, p2):
    width = p2[0] - p1[0]
    height = p2[1] - p1[1]
    
    cv.SetImageROI(image, (p1[0], p1[1], width, height))
    newim = cv.CreateImage((width, height), 8, 3)
    cv.Copy(image, newim)
    cv.ResetImageROI(image)

    return newim


def FindLetters(image):
    
    image_size = cv.GetSize(image)
    dst = CurveInvertImg(image)

    hor = []
    fl = False
    for i in xrange(0, image_size[1]):
        res = 0
        for j in xrange(0, image_size[0]):
            res += dst[i, j]    
        if res == 0:
            if fl:
                fl = False
                hor.append(i)
        else:        
            if not fl:
                fl = True
                hor.append(i)

    rects = []
    for ind in xrange(0, len(hor), 2):
        fl = False
        up = True
        buff = []
        for j in xrange(0, image_size[0]):
            res = 0        
            for i in xrange(hor[ind], hor[ind + 1]):
                res += dst[i, j]        
            if res == 0:
                if fl:                
                    fl = False
                    if up:
                        buff.append( (j, hor[ind]) )                    
                    else:
                        buff.append( (j, hor[ind + 1]) )
                        rects.append(buff)
                        buff = []
                    up = not up
            else:            
                if not fl:
                    fl = True
                    if up:
                        buff.append( (j, hor[ind]) )                    
                    else:
                        buff.append( (j, hor[ind + 1]) )
                        rects.append(buff)
                        buff = []
                    up = not up
    return rects

def GetLetters(image):
    rects = FindLetters(image)
    res = []
    #
    dst = CurveInvertImg(image)
    for x in rects:
        res.append(CutFromImage(image, x[0], x[1]))

    return res

    
