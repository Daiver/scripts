
#create list from tuple
TupleToList = lambda tpl: [x for x in tpl]

class brect:
    '''
        This is rect 
    '''
    def __init__(self, l_pt, rsize, imsize):
        '''
            l_pt - initial left upper point
            rsize - initial rect size
            imsize - image size (uses for check boundary)
        '''
        #bad but i dont know how implement it better
        self.Set_l_pt(l_pt)
        self.Set_size(rsize)
        self.image_size = imsize

    def Set_l_pt(self, l_pt): self.l_pt = TupleToList(l_pt)

    def Set_size(self, rsize): self.size = TupleToList(rsize)

    def RectOnImage(self, image):
        pt1, pt2 = self.TwoPnt()
        return image[pt1[1]:pt2[1], pt1[0]:pt2[0]]

    def TwoPnt(self):
        '''
            returns brect as 2 point
        '''
        return (self.l_pt), (self.l_pt[0] + self.size[0], self.l_pt[1] + self.size[1])

    def Rect(self):
        '''
            returns brect as rect
        '''
        return (self.l_pt[0], self.l_pt[1], self.size[0], self.size[1])

    def Check_Boundary(self):
        return (
                self.l_pt[0] >= 0 and
                self.l_pt[1] >= 0 and
                self.l_pt[0] + self.size[0] < self.image_size[0] and
                self.l_pt[1] + self.size[1] < self.image_size[1]
            )
    
    def Correct_Boundary(self):
        '''
            Checks boundary and correct it
            If corrected then returns True, else False
        '''
        if self.Check_Boundary(): return False        
        #bad but i dont know how implement it better... again
        if self.l_pt[0] < 0: self.l_pt[0] = 0
        if self.l_pt[1] < 0: self.l_pt[1] = 0
        tmp = self.l_pt[0] + self.size[0] - self.image_size[0]
        if tmp >= 0: self.l_pt[0] -= tmp + 1
        tmp = self.l_pt[1] + self.size[1] - self.image_size[1]
        if tmp >= 0: self.l_pt[1] -= tmp + 1

        return True

    def Center(self):
        '''
            returns center of rect
        '''
        return (self.l_pt[0] + self.size[0] // 2,
                self.l_pt[1] + self.size[1] // 2)
