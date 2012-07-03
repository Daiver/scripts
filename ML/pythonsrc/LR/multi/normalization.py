
import numpy as np

def normalize(X, m):
    mu = np.zeros((1, m))
    sigma = np.zeros((1, m))

    mu = np.mean(X)
    sigma = np.std(X)

    trans = np.ones((m, 1))

    X = (X - trans * mu) / (trans * sigma)
    
    return X
