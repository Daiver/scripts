
import numpy as np

import loaddata as ld

import computeCost as cC

import gradientdescent as GD

X, Y, m = ld.load('ex1data.txt')#load X's and Y's m - len of dataset

theta = np.zeros((2, 1))#init fitting params

#should be 32.07
print 'Cost:', cC.compCost(X, Y, theta)

#Some gradient descent settings
iterations = 1500;
alpha = 0.01;


theta,J_history = GD.GDescent(X, Y, theta, alpha, iterations)
print 'theta: ',  theta

predict = np.dot( np.array([1, 2]).reshape(1, 2), theta )
print 'predict for 3.5', predict
