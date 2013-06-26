
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

size = (40, 25)

#ds = SupervisedDataSet(size[0] * size[1], 1)
ds = ClassificationDataSet(size[0] * size[1], nb_classes=2)


for i in xrange(1, 5):
    ds.addSample(FeaturesFromFile('pos/' + str(i) + '.jpg', size), [1])
    print i


for i in xrange(1, 5):
    ds.addSample(FeaturesFromFile('neg/' + str(i) + '.jpg', size), [0])
    print i

ds._convertToOneOfMany( )

net = buildNetwork(size[0] * size[1], 1000, ds.outdim, outclass=SoftmaxLayer)



try:
    st = time()
    f = open('___learned2', 'r')
    net = pickle.load(f)
    f.close()
    print 'loaded from file', time() - st
except:
    st = time()
    trainer = BackpropTrainer( net, dataset=ds, momentum=0.1, verbose=True, weightdecay=0.01)

    #trainer.trainOnDataset(ds, 10)
    #trainer.testOnData()
    trainer.trainEpochs( 10 )
    print 'Learning time:', time() - st
    f = open('___learned2', 'w')
    pickle.dump(net, f)
    f.close()

#print net.activate(FeaturesFromFile('pos/5.jpg'))

for i in xrange(1, 6):
    print i, 'pos', net.activate(FeaturesFromFile('pos/' + str(i) + '.jpg', size)).argmax()

for i in xrange(1, 6):
    print i, 'neg', net.activate(FeaturesFromFile('neg/' + str(i) + '.jpg', size)).argmax()
