
import numpy as np

import loaddata as ld

import cost

X, Y, m = ld.load('data.txt')

theta = np.zeros((2 + 1, 1))

print cost.costfunc(theta, X, Y, m)
