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

libtest = cdll.LoadLibrary('./libtest.so.1.0') #python should call function "_init"  here, but nothing happens

def getCamPos():
    tmpcp = CamPos()
    libtest._Z4workPv(pointer(tmpcp))
    return tmpcp

if __name__ == "__main__":
    while 1:
        #tmpcp = CamPos()
        #libtest._Z4workPv(pointer(tmpcp))
        tmpcp = getCamPos()
        print(tmpcp.x, tmpcp.y, tmpcp.z, tmpcp.tx, tmpcp.ty, tmpcp.tz)