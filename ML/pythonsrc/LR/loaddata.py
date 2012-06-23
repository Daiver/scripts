import numpy as np

def load(fname):

    lX = []
    lY = []
    
    for s in open(fname):
        buf = s.split(',')
        lX.append(1)
        lX.append(float(buf[0]))
        lY.append(float(buf[1]))
    n = len(lY)
    X = np.array(lX).reshape(n, 2)
    Y = np.array(lY).reshape(n, 1)
    return X, Y, n
