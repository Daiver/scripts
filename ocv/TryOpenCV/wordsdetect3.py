import cv

def FindLetters(image):
    
    image_size = cv.GetSize(image)
    dst = image

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


image = cv.LoadImage('text1.jpg')

image_size = cv.GetSize(image)
grayscale = cv.CreateImage(image_size, 8, 1)

#cv.Smooth(image, image, cv.CV_GAUSSIAN, 1, 1)

cv.CvtColor(image, grayscale, cv.CV_BGR2GRAY)
cv.EqualizeHist(grayscale, grayscale)

#result = cv.CreateImage(cv.GetSize(img), img.depth, 1)
cv.Threshold(grayscale, grayscale, 5, 255, cv.CV_THRESH_BINARY)
#cv.ShowImage('img2', grayscale)
cv.Erode(grayscale, grayscale, None, 1)

#cv.Threshold(grayscale, grayscale, 250, 500, cv.CV_THRESH_BINARY)



dst = cv.CreateImage(image_size, 8, 1)
cv.Canny(grayscale, dst, 120, 255, 3)

rects = FindLetters(dst)

print rects

for r in rects:
    cv.Rectangle(image, r[0], r[1], (0, 0, 255))
    

cv.ShowImage('img', image)

cv.WaitKey(100000)
