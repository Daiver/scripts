from random import random
from Oslam import online_slam

class Enviroment(object):
    def get_landmarks(self, agent):
        pass

class SimpleEnv(Enviroment):
    def __init__(self, landmarks):
        self.landmarks = landmarks

    def get_landmarks(self, agent):
        return [
                    [i, [mark[j] - agent.pos[j] for j in xrange(len(agent.pos))]] for i, mark in enumerate(self.landmarks) 
                        if sum(abs(mark[k]-agent.pos[k]) for k in xrange(len(agent.pos))) <= agent.vis_range
                ]

class Robot(object):
    def __init__(self, pos, vis_range, env, mes_noise, move_noise):
        self.pos = pos
        self.vis_range = vis_range
        self.env = env
        self.mes_noise = mes_noise
        #this dict transform original descriptorrs into indexes
        self.move_noise = move_noise
        self.already_seen_landmark = {}#cut my arms

    def sense(self):
        marks = self.env.get_landmarks(self)#marks is [desc[x, y]]
        res = []
        for lm in marks: 
            if lm[0] not in self.already_seen_landmark:
                self.already_seen_landmark[lm[0]] = len(self.already_seen_landmark) 
            new_coo = lm[1][:]
            for i in xrange(len(new_coo)):new_coo[i] += self.rand() * self.move_noise
            tmp = [self.already_seen_landmark[lm[0]]]#, new_coo]
            for c in new_coo: tmp.append(c)
            res += [tmp]
        return res

    def rand(self):
            return random() * 2.0 - 1.0

    def move(self, dpos):
        res = []
        for i in xrange(len(self.pos)):
            res.append(dpos[i] + self.rand() * self.move_noise)
            self.pos[i] += res[i]
        return res 

def make_data(steps, env, agent):
    data = []
    for st in steps:
        Z = agent.sense()
        pos = agent.move(st)
        data += [[Z, pos]]
    return data

landmarks = [
                [10., 20.],
                [40., 8.],
                [35., 120.],
            ]

world_size = 200

if __name__ == '__main__':
    env = SimpleEnv(landmarks)
    robot = Robot([30., 30.], 40, env, 0.01, 0.01)
    path = [[1., 1.], [1., 1.], [1., 1.], [1., 1.],] 
    for i in xrange(2):
        path.append([0.0, 5.0])
    data = make_data(path, env, robot)
    print data
    mu, om = online_slam(data, len(robot.already_seen_landmark), 1., 1., (30., 30.))
    mu.show('mu')
    print robot.pos[0], robot.pos[1]
    print robot.already_seen_landmark
    #showall(landmarks, robot, 1000)



