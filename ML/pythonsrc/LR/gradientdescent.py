
import numpy as np

import computeCost as cC

def GDescent(X, Y, theta, alpha, num_iters):
    m = float(Y.size)
    J_history = np.zeros((num_iters, 1))

    for iter in xrange(0, num_iters):
        
        th0 = theta[0, 0] - alpha * (1/m) * np.dot((np.dot(X, theta) - Y).T , X[:, 0])
        th1 = theta[1, 0] - alpha * (1/m) * np.dot((np.dot(X, theta) - Y).T , X[:, 1])
        #th2 = - alpha * (1/m) * np.dot( (np.dot(X, theta) - Y).T, X[:, 1])
        #print th2, alpha *  (1/m)
        
        theta[0, 0] = th0
        theta[1, 0] = th1

        J_history[iter] = cC.compCost(X, Y, theta)
        
    return theta, J_history
