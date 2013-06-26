import random


class Link:
    def __init__(self, neuron):
        self.Neuron = neuron
        #self.weight = 0
        self.weight = random.random() 
