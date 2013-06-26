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
cv.Canny(grayscale, dst, 19, 100, 3)

storage = cv.CreateMemStorage(0)

seq = cv.FindContours(dst, storage, cv.CV_RETR_CCOMP, cv.CV_CHAIN_APPROX_SIMPLE)

for x in seq:
    print x

cv.ShowImage('img', dst)

cv.WaitKey(10000)
