from Oslam import online_slam
import cv2
import numpy as np

landmarks = [
                [10., 20.],
                [40., 8.],
                [35., 120.],
            ]

world_size = 200

class Robot(object):
    def __init__(self, x, y, sense_power):
        self.x = x
        self.y = y
        self.sense_power = sense_power

    def sense(self):
        res = []
        for i, l in enumerate(landmarks):
            #dist = np.sqrt( (self.x - l[0])**2 + (self.y - l[1])**2 )
            dx = l[0] - self.x
            dy = l[1] - self.y
            if (abs(dx) + abs(dy)) <= self.sense_power:
                res.append([i, dx, dy])
        return res

    def simple_move(self, dx, dy):
        self.x += dx
        self.y += dy

def make_data(steps, landmarks, robot):
    data = []
    for st in steps:
        Z = robot.sense()
        robot.simple_move(st[0], st[1])
        data.append([Z, [st[0], st[1]]])
        showall(landmarks, robot, 30)
    return data

def showall(landmarks, robot, waiting=0):
    tmp = np.zeros((world_size, world_size, 3))
    tmp[:] = 255
    for l in landmarks:
        cv2.circle(tmp, (int(l[0]), int(l[1])), 3, (255, 0, 0))
    cv2.circle(tmp, (int(robot.x), int(robot.y)), 3, (0, 255, 0))
    cv2.imshow('', tmp)
    cv2.waitKey(waiting)

if __name__ == '__main__':
    robot = Robot(30., 30., 40)
    path = [[1., 1.], [1., 1.], [1., 1.], [1., 1.],] 
    for i in xrange(20):
        path.append([0.0, 5.0])
    data = (make_data(path, landmarks, robot))
    print data
    mu, om = online_slam(data, len(path) + 1, len(landmarks), 1., 1., (30., 30.))
    mu.show('mu')
    print robot.x, robot.y
    showall(landmarks, robot, 1000)
