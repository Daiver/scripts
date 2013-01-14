from random import random

class Enviroment(object):
    def __init__(self):
        pass

    def get_landmarks(self, agent):
        pass

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
            res += [self.already_seen_landmark[lm[0]], new_coo] 
        return res

    def rand(self):
            return random() * 2.0 - 1.0

    def move(self, dpos):
        for i in xrange(len(self.pos)):
            self.pos[i] += dpos[i] + self.rand() * self.move_noise
        return self.pos

def make_data(steps, env, agent):
    data = []
    for st in steps:
        Z = agent.sense()
        pos = agent.move_noise(st)
        data += [Z, pos]
    return data




