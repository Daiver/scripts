from ctypes import *
import time
import struct
class CamPos(Structure):
    _fields_ = [
            ("x", c_float),
            ("y", c_float),
            ("z", c_float),
            ("tx", c_float),
            ("ty", c_float),
            ("tz", c_float),
        ]

i = 0
while 1:
    print('\ni:%d' % i)
    libtest = cdll.LoadLibrary('./libtest.so.1.0') #python should call function "_init"  here, but nothing happens
    tmpcp = CamPos()
    libtest._Z4workPv(pointer(tmpcp))
    print(tmpcp.tx)
    time.sleep(0.1)
