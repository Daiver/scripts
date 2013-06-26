
from time import time

import pybrain
from pybrain.datasets import *
from pybrain.tools.shortcuts import buildNetwork
from pybrain.supervised.trainers import BackpropTrainer

import pickle

from imgwork import FeaturesFromFile, FeaturesFromImg

size = (80, 50)

ds = SupervisedDataSet(size[0] * size[1], 1)

for i in xrange(1, 5):
    ds.addSample(FeaturesFromFile('pos/' + str(i) + '.jpg', size), (1, ))
    print i


for i in xrange(1, 5):
    ds.addSample(FeaturesFromFile('neg/' + str(i) + '.jpg', size), (0, ))
    print i

net = buildNetwork(size[0] * size[1], 3000, 1, bias=True)

st = time()

'''
try:
    f = open('_learned', 'r')
    net = pickle.load(f)
    f.close()
except:
'''

if True:
    trainer = BackpropTrainer(net, learningrate = 0.01, momentum = 0.99)
    trainer.trainOnDataset(ds, 10)
    trainer.testOnData()
    print 'Learning time:', time() - st
    #f = open('_learned', 'w')
    #pickle.dump(net, f)
    #f.close()

#print net.activate(FeaturesFromFile('pos/5.jpg'))

for i in xrange(1, 6):
    print i, 'pos', net.activate(FeaturesFromFile('pos/' + str(i) + '.jpg', size))

for i in xrange(1, 6):
    print i, 'neg', net.activate(FeaturesFromFile('neg/' + str(i) + '.jpg', size))
