import cv


startindex = 65

numofletters = 26


def TrainingText():

    img = cv.CreateImage((1500, 500), 8, 3)

    cv.FloodFill(img, (0, 0), (255, 255, 255)) #.Rectangle(img, (0, 0), (500, 100), (255, 255, 255))

    #cvPutText(image, "Hello World!", cvPoint(50, 50), &font, CV_RGB(0,255,255));

    fonts = [
            cv.InitFont(cv.CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, 1.0),
            cv.InitFont(cv.CV_FONT_HERSHEY_COMPLEX, 1.0, 1.0),
            cv.InitFont(cv.CV_FONT_HERSHEY_DUPLEX, 1.0, 1.0),
            cv.InitFont(cv.CV_FONT_HERSHEY_PLAIN, 1.0, 1.0),
            #cv.InitFont(cv.CV_FONT_HERSHEY_SCRIPT_COMPLEX, 1.0, 1.0)
            cv.InitFont(cv.CV_FONT_HERSHEY_SCRIPT_SIMPLEX, 1.0, 1.0),
            cv.InitFont(cv.CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0),
            cv.InitFont(cv.CV_FONT_HERSHEY_TRIPLEX, 1.0, 1.0),
            cv.InitFont(cv.CV_FONT_ITALIC, 1.0, 1.0)
        ]

    #font = cv.InitFont(cv.CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, 1.0)

    for j in xrange(0, len(fonts)):

        for i in xrange(0, numofletters):
            cv.PutText(img, chr(startindex + i), (10 + i * 40, 30 + j * 50), fonts[j], (255, 0, 0))

    return img
    #cv.ShowImage('o', img)

    #cv.WaitKey(1000)
