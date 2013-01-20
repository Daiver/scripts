import cv2

feature_params = dict( maxCorners = 500, 
    qualityLevel = 0.03,
    minDistance = 5,
    blockSize = 5 )

if __name__ == '__main__':
    img = cv2.imread('1.jpg')
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    points = cv2.goodFeaturesToTrack(gray, mask = None, **feature_params)
    for p in points:
        cv2.circle(img, (p[0][0], p[0][1]), 5, (0, 255, 0))
        #print(p[0])
    #gray  = cv2.Sobel(gray, cv2.CV_32F, 1, 1, ksize=5)
    #points = cv2.goodFeaturesToTrack(gray, 500, 0.3, 7, 7, mask=None)
    #gray  = cv2.Sobel(gray, cv2.CV_32F, 0, 1)
    #gray  = cv2.Sobel(gray, cv2.CV_32F, 0, 1)
    cv2.imshow('', img)
    cv2.waitKey()
