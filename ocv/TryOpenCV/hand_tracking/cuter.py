
import sys

import cv

class Viewer:
    def __init__(self, image):
        self.image = image
        self.cur_key = 255

        self.cursor = (0, 0)
        self.polygon = []

        #defininig constans
        self.l_a = 81
        self.u_a = 82
        self.r_a = 83
        self.d_a = 84

        self.space_but = 32
        self.exit_but = 27

        self.b_but = 98
        self.s_but = 115
        self.r_but = 114

        self.arrow_step = 3
        self.arrow_work = {
                self.l_a : lambda point : (point[0] - self.arrow_step, point[1]),
                self.u_a : lambda point : (point[0], point[1] - self.arrow_step),
                self.r_a : lambda point : (point[0] + self.arrow_step, point[1]),
                self.d_a : lambda point : (point[0], point[1] + self.arrow_step)
            }

    def DrawOn(self, image):

        pol_len = len(self.polygon)
        if pol_len > 0:
            for x in self.polygon:
                cv.Circle(image, x, 2, (0, 255, 255), 3)
            if pol_len > 1:
                for i in xrange(1, pol_len):
                    cv.Line(image, self.polygon[i - 1], self.polygon[i], (0, 255, 255))
        cv.Circle(image, self.cursor, 3, (255, 0, 0), 3)

    def Mk_tmp_img(self):
        size = cv.GetSize(self.image)
        toview = cv.CreateImage(size, 8, 3)
        cv.Copy(self.image, toview)
        return toview

    def ClearOutSide(self):
        if len(self.polygon) < 2: return

        tmp = self.Mk_tmp_img()
        for i in xrange(1, len(self.polygon)):
            cv.Line(tmp, self.polygon[i - 1], self.polygon[i], (0, 0, 0))

        size = cv.GetSize(tmp)
        verifypoint = lambda point : point[0] >= 0 and point[1] >= 0 and point[0] < size[1] and point[1] < size[0]
        stack = [(0, 0)]
        counter = 0
        pointstocute = {}
        
        while (len(stack) > 0) and counter < size[0] * size[1]:
            point = stack.pop()
            counter += 1
            print len(stack)
            if not verifypoint(point) : continue
            if tmp[point[0], point[1]] == (0, 0, 0) or point in pointstocute: continue

            pointstocute[point] = 1
            
            stack.append((point[0] - 1, point[1]))
            stack.append((point[0] + 1, point[1]))
            stack.append((point[0], point[1] - 1))
            stack.append((point[0], point[1] + 1))
        for point, y in pointstocute.iteritems():
            self.image[point[0], point[1]] = (255, 255, 255)
        
    def ProcessKey(self):
        if self.cur_key == 255: return

        if self.cur_key in self.arrow_work:
            self.cursor = self.arrow_work[self.cur_key](self.cursor)

        if self.cur_key == self.space_but:
            self.polygon.append(self.cursor)
            
        if self.cur_key == self.r_but:
            self.polygon = []

        if self.cur_key == self.s_but:
            cv.SaveImage('cuted.jpg', self.image)

        if self.cur_key == self.b_but:
            self.ClearOutSide()

        self.cur_key = 255

    def Run(self):
        while self.cur_key != self.exit_but:
            self.View()
        
    def View(self):
        toview = self.Mk_tmp_img()
        
        self.ProcessKey()

        self.DrawOn(toview)
        
        cv.ShowImage('image', toview)
        k = cv.WaitKey(10) % 0x100
        if k !=255 :
            self.cur_key = k
            print 'pressed', k


if len(sys.argv) < 2:
    print 'use with filename'
    exit()

image = None

try:
    image = cv.LoadImage(sys.argv[1])
except:
    print 'Cant load image'
    exit()

viewer = Viewer(image)
viewer.Run()
