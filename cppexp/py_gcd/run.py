import ctypes
lib = ctypes.cdll.LoadLibrary('./libpygcd.so.1.0')
#lib._Z4workv()
#lib._Z5work2ii(2, 4)
def f(p): print p
def f2(i): print i**2
#lib._Z5work3PFPvS_E(ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_void_p)(f))

#lib._Z5work3PFPviE(ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int)(f))
lib._Z5work3PFPviE(ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_int)(f2))
