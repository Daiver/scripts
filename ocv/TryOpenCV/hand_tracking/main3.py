
from time import time

import pybrain
from pybrain.datasets            import ClassificationDataSet
from pybrain.utilities           import percentError
from pybrain.tools.shortcuts     import buildNetwork
from pybrain.supervised.trainers import BackpropTrainer
from pybrain.structure.modules   import SoftmaxLayer

from pylab import ion, ioff, figure, draw, contourf, clf, show, hold, plot
from scipy import diag, arange, meshgrid, where
from numpy.random import multivariate_normal

import pickle

from imgwork import FeaturesFromFile, FeaturesFromImg

import cv

size = (80, 50)

#ds = SupervisedDataSet(size[0] * size[1], 1)
ds = ClassificationDataSet(size[0] * size[1], nb_classes=2)


for i in xrange(0, 300):
    ds.addSample(FeaturesFromFile('hand3/pos/' + str(i) + '.jpg', size), [1])
    print i


for i in xrange(0, 300):
    ds.addSample(FeaturesFromFile('hand3/neg/' + str(i) + '.jpg', size), [0])
    print i

ds._convertToOneOfMany( )

net = buildNetwork(size[0] * size[1], 2000, ds.outdim, outclass=SoftmaxLayer)
print ds.outdim

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
    trainer = BackpropTrainer( net, dataset=ds, momentum=0.1, verbose=True, weightdecay=0.01)

    #trainer.trainOnDataset(ds, 10)
    #trainer.testOnData()
    print 'start train'
    trainer.trainEpochs( 50 )
    print 'Learning time:', time() - st
    f = open('___learned3', 'w')
    pickle.dump(net, f)
    f.close()

#print net.activate(FeaturesFromFile('pos/5.jpg'))

counter = 0

for i in xrange(300, 400):
    image = cv.LoadImage('hand3/pos/' + str(i) + '.jpg', cv.CV_LOAD_IMAGE_GRAYSCALE)
    print i, 'pos', net.activate(FeaturesFromImg(image, size)).argmax()
    if net.activate(FeaturesFromImg(image, size)).argmax() == 1:
        counter += 1

    #cv.ShowImage('', image)
    #cv.WaitKey(10000)
print 'pos', counter, '/100'
counter = 0

for i in xrange(300, 400):
    image = cv.LoadImage('hand3/neg/' + str(i) + '.jpg', cv.CV_LOAD_IMAGE_GRAYSCALE)
    if net.activate(FeaturesFromImg(image, size)).argmax() == 0:
        counter += 1

    print i, 'neg', net.activate(FeaturesFromImg(image, size)).argmax()
    #cv.ShowImage('', image)
    #cv.WaitKey(10000)
    #print i, 'neg', net.activate(FeaturesFromFile('hand/neg/' + str(i) + '.jpg', size)).argmax()
print 'neg', counter, '/100'

image = cv.LoadImage('hand3/handimg/raw.jpg', cv.CV_LOAD_IMAGE_GRAYSCALE)
print net.activate(FeaturesFromImg(image, size)).argmax()
