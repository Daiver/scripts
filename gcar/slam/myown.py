from Oslam import online_slam
import cv2
import numpy as np

landmarks = [
                [10., 20.],
                [40., 8.],
                [35., 120.],
            ]

world_size = 200

class Agent(object):
    def __init__(self, x, y, sense_power):
        self.x = x
        self.y = y
        self.sense_power = sense_power

    def sense(self):
        res = []
        for i, l in enumerate(landmarks):
            #dist = np.sqrt( (self.x - l[0])**2 + (self.y - l[1])**2 )
            dx = l[0] - self.x
            dy = l[0] - self.y
            if (abs(dx) + abs(dy)) <= self.sense_power:
                res.append([i, dx, dy])
        return res

def showall(landmarks, waiting=0):
    tmp = np.zeros((world_size, world_size, 3))
    tmp[:] = 255
    for l in landmarks:
        cv2.circle(tmp, (int(l[0]), int(l[1])), 3, (255, 0, 0))
    cv2.imshow('', tmp)
    cv2.waitKey(waiting)

if __name__ == '__main__':
    showall(landmarks)
