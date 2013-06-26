
import sys

import cv

from letterdetect import *

from Network.Network import *

from pybrain.datasets            import ClassificationDataSet
from pybrain.utilities           import percentError
from pybrain.tools.shortcuts     import buildNetwork
from pybrain.supervised.trainers import BackpropTrainer
from pybrain.structure.modules   import SoftmaxLayer


size = (20, 20)#size of image for NN

def GetInp(image, size):#convert image to list of features for NN    
    newimg = cv.CreateImage(size, image.depth, image.nChannels );
    cv.Resize(image, newimg)
    image_size = cv.GetSize(newimg)
    grayscale = cv.CreateImage(image_size, 8, 1)
    cv.CvtColor(newimg, grayscale, cv.CV_RGB2GRAY)
    
    res = []

    for i in xrange(0, size[1]):
        for j in xrange(0, size[0]):
            res.append(255 - grayscale[i, j])#dark pix is more important            
    return res    


IMAGE_NAME = 'text4.jpg'

if len(sys.argv) == 2:#you can change img name
        IMAGE_NAME = sys.argv[1]

image = cv.LoadImage(IMAGE_NAME)
image_size = cv.GetSize(image)

rects = FindLetters(image)#find letters

for r in rects:#draw rects around symbols
    cv.Rectangle(image, r[0], r[1], (0, 0, 255))
    
images = GetLetters(image)#split image to symbols images

cv.ShowImage('img', image)
print 'press any key'
cv.WaitKey(100000)

print 'Number of images:', len(images)

ds = ClassificationDataSet( size[0] * size[1] , 1, nb_classes=10)#SupervisedDataSet(150, 10)


#10 samples for learning
print 'Start learning'
for i in xrange(0, 30):    
    ds.addSample(GetInp(images[i], size), [i % 10])
    print '#', i % 10

ds._convertToOneOfMany()

net = buildNetwork( ds.indim, 400, ds.outdim, outclass=SoftmaxLayer )#buildNetwork(150, 400, 200, 10, bias=True)

trainer = BackpropTrainer( net, dataset=ds, momentum=0.1, verbose=True, weightdecay=0.01)

for i in range(10):
    trainer.trainEpochs(10)

#trainer.trainUntilConvergence()

#BackpropTrainer(net, learningrate = 0.01, momentum = 0.99)
#trainer.trainOnDataset(ds, 100)
#trainer.testOnData()

print 'finish learning'

#prediction by NN

for i in xrange(0, 70):
    cv.ShowImage('img', images[i])
    outdata = ClassificationDataSet(size[0] * size[1],1, nb_classes=10)
    outdata.addSample(GetInp(images[i], size), [0])
    outdata._convertToOneOfMany()
    out = net.activateOnDataset(outdata)
    out = out.argmax(axis=1)
    
    print 'out:', out
    #print 'Image number', i, 'of', len(images), ' prediction:', network.Handle(GetInp(images[i], size)).Value
    print 'press any key'
    cv.WaitKey(100000)

cv.WaitKey(100000)

