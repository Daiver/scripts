from ctypes import *
libtest = cdll.LoadLibrary('./libtest.so.1.0') #python should call function "_init"  here, but nothing happens
libtest._Z4workv()
