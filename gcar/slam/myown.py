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
    def __init__(self, x, y):
        self.x = x
        self.y = y

def showall(landmarks, waiting=0):
    tmp = np.zeros((world_size, world_size, 3))
    tmp[:] = 255
    for l in landmarks:
        cv2.circle(tmp, (int(l[0]), int(l[1])), 3, (255, 0, 0))
    cv2.imshow('', tmp)
    cv2.waitKey(waiting)

if __name__ == '__main__':
    showall(landmarks)
