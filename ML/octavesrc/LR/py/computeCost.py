
import numpy as np

def compCost(X, Y, theta):
    m = Y.size

    prediction = np.dot(X, theta)
    return sum((prediction - Y) ** 2) * 1/(2 * m)
