
from random import random

from time import time

import numpy as np

curry = lambda func_object, *args: (
    lambda *local_args: (
        func_object(
            *(args + local_args)
    )
    )
)

theta = np.array([1.0 - 2 * random() for i in xrange(9)])

def extractthetas(theta, ins, hiddens, outs, biass=False):
    bis = 1 if biass else 0
    fstindex = (bis + ins) * hiddens
    secindex = (bis + hiddens) * outs + fstindex
    return [theta[:fstindex].reshape((ins, hiddens)), theta[fstindex:secindex].reshape((hiddens, outs))]

def packtheta(theta):
    res = []
    for t in theta:
        for x in t:
            res += [x]
    return np.array(res)

#print packtheta()

def ANNActivation(size, actfunc, theta, x):
    theta = extractthetas(theta, size[0], size[1], size[2], False)
    a = x
    for th in theta:
        a = actfunc(np.dot(a, th))
    return a
#print ANNActivation(theta, np.tanh, np.array([1, 2]))
'''
def model(thetas, x):
    return np.tanh(np.dot(x.T, thetas))
'''
def error(thetas, model, X, Y):
    pred = np.array([model(thetas, X[i]) for i in xrange(X.shape[0])])
    return sum(1.0 / (2 * len(Y)) * sum((pred - Y)**2))
    #return sum([singleerror(thetas, model, X[i], Y[i]) for i in xrange(len(Y))]) / len(Y)

def singleerror(thetas, model, x, y):
    return sum(1.0 / 2 * (model(thetas, x) - y)**2)

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

layerssize = (2, 2, 1,)

def NNGrad(thetas, model, x, y):
    theta = extractthetas(theta, size[0], size[1], size[2], False)
    
    theta_grad0 = np.zeros(len(theta[0]))
    theta_grad1 = np.zeros(len(theta[1]))
    

def train(thetas, model, X, Y):
    Q = error(thetas, model, X, Y)
    lambd = 1.0 / len(Y)
    nu = 0.01
    while Q > 0.01:
        i = int(random() * len(Y))
        e = singleerror(thetas, model, X[i], Y[i])
        dW = puregrad(thetas, X[i], Y[i])
        thetas = thetas - nu*dW
        #Q = error(thetas, model, X, Y)
        #print Q#, thetas
        Q = (1 - lambd)*Q + lambd*e
    return thetas
    

X = [
        [1, 1],
        [0, 1],
        [1, 0],
        [0, 0]
    ]
X = np.array(X)

Y = [
        0,
        1,
        1,
        0
    ]
Y = np.array(Y)

model = curry(ANNActivation, layerssize, np.tanh)
#print error(theta, model, X, Y)

#print puregrad(thetas, X[0], Y[0])
st = time()
theta = train(theta, model, X, Y)
print 't', time() - st
print error(theta, model, X, Y)
print theta
print model(theta, np.array([1, 1]))
