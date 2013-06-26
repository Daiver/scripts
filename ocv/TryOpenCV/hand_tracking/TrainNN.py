
from time import time

import os

import pybrain
from pybrain.datasets            import ClassificationDataSet
from pybrain.utilities           import percentError
from pybrain.tools.shortcuts     import buildNetwork
from pybrain.supervised.trainers import BackpropTrainer, RPropMinusTrainer
from pybrain.structure.modules   import SoftmaxLayer


#from scipy import diag, arange, meshgrid, where
#from numpy.random import multivariate_normal

import pickle

from imgwork import FeaturesFromFile, FeaturesFromImg


import cv


def ListFromDir(directory):
    return [directory + '/' + i for i in os.listdir(directory)]


size = (25, 25)

'''
best params:
size = (25, 25)


for i in xrange(0, 1000):

for i in xrange(0, 962): lol


net = buildNetwork(size[0] * size[1], 96, ds.outdim, outclass=SoftmaxLayer)
'''

#ds = SupervisedDataSet(size[0] * size[1], 1)
ds = ClassificationDataSet(size[0] * size[1], nb_classes=2)

#print ds.outdim
#exit()

print 'start loading'

st = time()
posnames = ListFromDir('images/pos')
print 'loading pos examples'
for i in xrange(0, 40000):
    ds.addSample(FeaturesFromFile(posnames[i], size), [1])
    #print i

negnames = ListFromDir('images/new_neg')
print 'loading neg examples'
for i in xrange(0, 40000):
    ds.addSample(FeaturesFromFile(negnames[i], size), [0])
    #print i

print 'finish loading', time() - st

ds._convertToOneOfMany( )

net = buildNetwork(size[0] * size[1], 400, ds.outdim, outclass=SoftmaxLayer)
'''
try:
    st = time()
    f = open('___learned3', 'r')
    net = pickle.load(f)
    f.close()
    print 'loaded from file', time() - st
except:
'''
#exit()
if True:
    st = time()
    trainer = RPropMinusTrainer(net, dataset=ds, momentum=0.1, verbose=True, weightdecay=0.01)#
    #trainer = BackpropTrainer( net, dataset=ds, momentum=0.1, verbose=True, weightdecay=0.01)    

    #trainer.trainOnDataset(ds, 10)
    #trainer.testOnData()
    print 'start train'
    trainer.trainEpochs( 100 )
    #trainer.trainUntilConvergence()
    print 'Learning time:', time() - st
    f = open('___learned3', 'w')
    pickle.dump(net, f)
    f.close()

#print net.activate(FeaturesFromFile('pos/5.jpg'))
counter = 0

st = time()
for i in xrange(40000, 50000):
    image = cv.LoadImage(posnames[i], cv.CV_LOAD_IMAGE_GRAYSCALE)
    res = net.activate(FeaturesFromImg(image, size)).argmax()
    #print i, 'pos', res
    if res == 1:
        counter += 1

    #cv.ShowImage('', image)
    #cv.WaitKey(10000)
print 'pos', counter, '/1000'
print 'time', time() - st

counter = 0
st = time()
for i in xrange(40000, 50000):
    image = cv.LoadImage(negnames[i], cv.CV_LOAD_IMAGE_GRAYSCALE)
    res = net.activate(FeaturesFromImg(image, size)).argmax()
    if res == 0:
        counter += 1

    #print i, 'neg', res
    
print 'neg', counter, '/1000'
print 'time', time() - st

image = cv.LoadImage('images/handimg/0.jpg', cv.CV_LOAD_IMAGE_GRAYSCALE)
print net.activate(FeaturesFromImg(image, size)).argmax()
