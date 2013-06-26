
import os

import cv2

import numpy as np

import pybrain
from pybrain.datasets            import ClassificationDataSet
from pybrain.utilities           import percentError
from pybrain.tools.shortcuts     import buildNetwork
from pybrain.supervised.trainers import BackpropTrainer, RPropMinusTrainer, rprop
from pybrain.structure.modules   import SoftmaxLayer

from time import time


def ListFromDir(directory):
    return [directory + '/' + i for i in os.listdir(directory)]

def FeaturesFromImage(image, size):
    if len(image.shape) >= 3:
        image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    return cv2.resize(image, size).reshape((-1)).tolist()

def FeaturesFromFile(fname, size):
    return FeaturesFromImage(cv2.imread(fname), size)

def dsfromfilelist(poslist, neglist, size):
    ds = ClassificationDataSet(size[0] * size[1], nb_classes=2)
    for x in poslist:
        ds.addSample(FeaturesFromFile(x, size), [1])
    for x in neglist:
        ds.addSample(FeaturesFromFile(x, size), [0])

    return ds

posnames = ListFromDir('images/pos')
negnames = ListFromDir('images/new_neg')
    
def dsfromnumber(pos, neg, size):
    return dsfromfilelist(posnames[:pos], negnames[:pos], size)

def CrossValidation(net, pos, neg, size):
    poslist = posnames[:pos]
    neglist = negnames[:neg]
    
    counter = 0
    for x in poslist:
        res = net.activate(FeaturesFromImage(cv2.imread(x), size)).argmax()
        if res == 1:
            counter += 1
    pos_test = counter
    
    counter = 0
    for x in neglist:
        res = net.activate(FeaturesFromImage(cv2.imread(x), size)).argmax()
        if res == 0:
            counter += 1
    return pos_test, counter

def BnTNN(ds, hiddensize, epoches):
    net = buildNetwork(ds.indim, hiddensize, ds.outdim, outclass=SoftmaxLayer)
    st = time()
    trainer = RPropMinusTrainer(net, dataset=ds, momentum=0.1, verbose=True, weightdecay=0.01)#
    trainer.trainEpochs( epoches )
    return net

size = (25, 25)

ds = dsfromnumber(5000, 5000, size)
print ds
net = BnTNN(ds, 30, 100)
print net
print CrossValidation(net, 100, 100, size)
'''
img = cv2.imread('images/pos/1.jpg')#[10:20, 10:50]
print img.shape

img = img.reshape((-1))
#img = cv2.resize(img, (100, 100))

cv2.imshow('', img)
cv2.waitKey(1000)

'''
