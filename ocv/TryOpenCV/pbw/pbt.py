from time import time

import pybrain
from pybrain.datasets import *
from pybrain.tools.shortcuts import buildNetwork
from pybrain.supervised.trainers import BackpropTrainer
import pickle

if __name__ == "__main__":
	ds = SupervisedDataSet(2, 1)
	ds.addSample( (0,0) , (0,))
	ds.addSample( (0,1) , (1,))
	ds.addSample( (1,0) , (1,))
	ds.addSample( (1,1) , (0,))

	net = buildNetwork(2, 4, 1, bias=True)
        
	try:
		f = open('_learned', 'r')
		net = pickle.load(f)
		f.close()
	except:
		st = time()

		trainer = BackpropTrainer(net, learningrate = 0.01, momentum = 0.99)
		trainer.trainOnDataset(ds, 1000)
		trainer.testOnData()
		print time() - st
		f = open('_learned', 'w')
		pickle.dump(net, f)
		f.close()


	print net.activate((0,0))
	print net.activate((1,0))
	print net.activate((0,1))
	print net.activate((1,1))
