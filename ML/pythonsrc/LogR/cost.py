
import numpy as np

from sigmoid import sigmoid

def costfunc(theta, X, Y, m):
    m = float(m)
    res = 0

    #print np.dot(theta.T, X)
    h = sigmoid( np.dot(X, theta) )
    
    #tmp = ( Y.T * np.log(h) ) + ((1 - Y.T) * np.log(1 - h))
    tmp = np.dot( Y.T, np.log(h) ) + np.dot((1 - Y.T), np.log(1 - h))


    res = - (1 / m * tmp)

    #tmp = 1 / m * np.dot(X.T, (h - Y))

    return res


