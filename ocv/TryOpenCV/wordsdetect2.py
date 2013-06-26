import cv

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

dst = cv.CreateImage(image_size, 8, 1)
cv.Canny(grayscale, dst, 120, 255, 3)

storage = cv.CreateMemStorage(0)

'''cv.ShowImage('img2', grayscale)

seq = cv.FindContours(dst, storage, cv.CV_RETR_LIST  , cv.CV_CHAIN_APPROX_SIMPLE)

for x in seq:
    print x'''

        
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
print hor

vert = []
for ind in xrange(0, len(hor), 2):
    fl = False
    for j in xrange(0, image_size[0]):
        res = 0
        #for i in xrange(0, image_size[1]):
        for i in xrange(hor[ind], hor[ind + 1]):
            res += dst[i, j]
        
        if res == 0:
            if fl:
                fl = False
                vert.append((ind, j))
        else:
            
            if not fl:
                fl = True
                vert.append((ind, j))

print vert

        
for p in hor:
    cv.Line(image,(0, p) , (image_size[0], p), (255,0,0))
        
for p in vert:
    cv.Line(image,(p[1], hor[p[0]]) , (p[1], hor[p[0] + 1]), (255,0,0))

points = []
for i in xrange(0, len(vert)):
    points.append( ( (vert[i][1], hor[vert[i][0]]), (vert[i][1], hor[vert[i][0] + 1]) ) )

for i in xrange(0, len(points) -1):
    cv.Circle(image, points[i][0], 3 , (0, 255, 0))
    cv.Circle(image, points[i + 1][1], 3 , (0, 0, 255))
    

cv.ShowImage('img', image)

cv.WaitKey(10000)
