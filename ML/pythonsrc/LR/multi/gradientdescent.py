
import numpy as np

def GDescent(X, Y, theta, alpha, iterations):
    m = float(Y.size)
    for j in xrange(0, iterations):
     
        predictiongrad = np.dot( (np.dot(X, theta) - Y).T, X)
        #print j, predictiongrad.T
        theta -= alpha * (1 / m) * predictiongrad.T

    return theta
