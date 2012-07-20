
import numpy as np

import loaddata as ld

import computeCost as cC

import gradientdescent as GD

import math


X, Y, m = ld.load('ex1data.txt')#load X's and Y's m - len of dataset

theta = np.zeros((2, 1))#init fitting params

#should be 32.07
print 'Cost:', cC.compCost(X, Y, theta)

#Some gradient descent settings
iterations = 1500;
alpha = 0.01;


theta,J_history = GD.GDescent(X, Y, theta, alpha, iterations)
print 'theta: ',  theta


pvalue = 3.5
#predict = 1/(1+ math.exp( np.dot( np.array([1, pvalue]).reshape(1, 2), theta)))
predict = np.dot( np.array([1, pvalue]).reshape(1, 2), theta )
print 'predict for ',pvalue, predict
