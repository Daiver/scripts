import ctypes
from time import time

lib = ctypes.cdll.LoadLibrary('./libpygcd.so.1.0')
#lib._Z4workv()
#lib._Z5work2ii(2, 4)
def f(p): print p
def f2(i): 
    x = i**2
    y = x**2
    for r in xrange(900000):
        y = y**5

#lib._Z5work3PFPvS_E(ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_void_p)(f))

#lib._Z5work3PFPviE(ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int)(f))
st = time()
lib._Z5work3PFPviE(ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int)(f2))
f1 = time() - st
st = time()

rng = range(20)
for i in rng: f2(i)
f2 = time() - st
print f1, f2
