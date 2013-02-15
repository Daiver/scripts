import pybrain
from pybrain.datasets import *
from pybrain.tools.shortcuts import buildNetwork
from pybrain.supervised.trainers import BackpropTrainer
import pickle
import numpy as np
from time import time

if __name__ == '__main__':
    ds = SupervisedDataSet(2, 1)

    for i in xrange(1, 5):
        ds.addSample(np.array([1, 0.1 * i]), (1, ))
        print i
        trainer = BackpropTrainer(net, learningrate = 0.01, momentum = 0.99)
        trainer.trainOnDataset(ds, 10)
        trainer.testOnData()
        print 'Learning time:', time() - st
