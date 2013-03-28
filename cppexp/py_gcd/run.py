import ctypes
lib = ctypes.cdll.LoadLibrary('./libpygcd.so.1.0')
#lib._Z4workv()
#lib._Z5work2ii(2, 4)
def f(): return 10000
lib._Z5work3PFivE(ctypes.CFUNCTYPE(ctypes.c_int)(f))
