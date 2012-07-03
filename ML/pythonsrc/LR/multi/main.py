# -*- coding: utf-8 -*-

import numpy as np

import loaddata as ld

import gradientdescent as GD

import normalization as norm

X, Y, n = ld.load('data.txt')

X = norm.normalize(X, n)

X = X.reshape((n * 2))

tmp = []
for i in xrange(0, 2 * n, 2):#Оторвать мне руки 
    tmp.append(1)
    tmp.append(X[i])
    tmp.append(X[i + 1])

X = np.array(tmp).reshape(n, 3)

print X

alpha = 0.01;
iterations = 400;

theta = np.zeros((3, 1))#init fitting params

theta = GD.GDescent(X, Y, theta, alpha, iterations)
print 'theta: ',  theta

price = np.dot([1, 1650, 3] , theta)

print price
