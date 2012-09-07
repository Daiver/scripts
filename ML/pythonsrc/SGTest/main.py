
from random import random

from time import time

import numpy as np

def model(thetas, x):
    return np.tanh(np.dot(x.T, thetas))

def error(thetas, model, X, Y):
    pred = np.array([model(thetas, X[i]) for i in xrange(X.shape[0])])
    return 1.0 / (2 * len(Y)) * sum((pred - Y)**2)
    #return sum([singleerror(thetas, model, X[i], Y[i]) for i in xrange(len(Y))]) / len(Y)

def singleerror(thetas, model, x, y):
    return 1.0 / 2 * (model(thetas, x) - y)**2

def puregrad(thetas, x, y):
    eps = 0.0001
    res = []
    for i in xrange(len(thetas)):
        thetas[i] += eps
        lf = singleerror(thetas, model, x, y)
        thetas[i] -= 2 * eps
        rf = singleerror(thetas, model, x, y)
        thetas[i] += eps
        res.append((lf - rf) / (2 * eps))
    return np.array(res)

def train(thetas, model, X, Y):
    Q = error(thetas, model, X, Y)
    lambd = 1/len(Y)
    nu = 0.5
    dW = [10000]
    while Q > 0.001:
        i = int(random() * len(Y))
        e = singleerror(thetas, model, X[i], Y[i])
        #print Q, thetas
        dW = puregrad(thetas, X[i], Y[i])

        thetas = thetas - nu*dW
        Q = error(thetas, model, X, Y)
        #Q = (1 - lambd)*Q + lambd*e
    return thetas
    

X = [
        [1, 1],
        [0, 1],
        [1, 0],
        [0, 0]
    ]
X = np.array(X)

Y = [
        1,
        1,
        1,
        0
    ]
Y = np.array(Y)

thetas = np.array([0.0, 0.0])
print error(thetas, model, X, Y)

#print puregrad(thetas, X[0], Y[0])
st = time()
thetas = train(thetas, model, X, Y)
print 't', time() - st
print error(thetas, model, X, Y)
print thetas
print model(thetas, np.array([0, 0]))
