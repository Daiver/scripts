import numpy as np

import loaddata as ld

import gradientdescent as GD

X, Y, n = ld.load('data.txt')

alpha = 0.01;
iterations = 400;

theta = np.zeros((3, 1))#init fitting params

theta = GD.GDescent(X, Y, theta, alpha, iterations)
print 'theta: ',  theta
print type(theta[0, 0])
