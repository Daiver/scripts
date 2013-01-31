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
libtest = cdll.LoadLibrary('./libtest.so.1.0') #python should call function "_init"  here, but nothing happens
while 1:
    print('\ni:%d' % i)
    try:
        tmpcp = CamPos()
        libtest._Z4workPv(pointer(tmpcp))
        print(tmpcp.x, tmpcp.y, tmpcp.z, tmpcp.tx, tmpcp.ty, tmpcp.tz)
    except:
        pass
    time.sleep(0.9)
