# -*- coding: utf-8 -*-

import re

import os

import sys

import urllib2

#import cv

from random import random

#from htmllib import HTMLParser

from commands import *

from time import time

def DownLoadFile(url, filename):
    open(filename, "w").write(urllib2.urlopen(url).read())

DE_NAME = 'unity'
setwallpapers = {}
from ubuntu import SetWallpaper
setwallpapers['unity'] = SetWallpaper
from awesome import SetWallpaper
setwallpapers['awesome'] = SetWallpaper

def ImageListFromGoodFon():
    page = urllib2.urlopen("http://www.goodfon.ru/mix.php")
    html = page.read()

    p = re.compile(r"/wallpaper/[0-9]+\.html")
    p2 = re.compile(r"[0-9]+")
    allWal = p.findall(html)

    res = []
    for walInd in xrange(len(allWal)):
        walIndex = p2.findall(allWal[walInd])
        width = 1366
        height = 768
        newUrl = "http://www.goodfon.ru/image/" + walIndex[0] + "-" + str(width) + "x" + str(height) + ".jpg"

        #filename = walIndex[0] + "-" + str(width) + "x" + str(height) + ".jpg"
        res += [newUrl]
    return res

def Refresh(imagelist, wallsetmeth):
    imagename = imagelist[int(random() * len(imagelist))]
    ROOT_PATH = os.getcwd()
    filename = '%s/%s%s.%s' % (ROOT_PATH, 'images_chache/', str(time()), imagename[-4:])
    DownLoadFile(imagename, filename)
    wallsetmeth(filename)

if len(sys.argv) > 1:
    DE_NAME = sys.argv[1]

st = time()
Refresh(ImageListFromGoodFon(), setwallpapers[DE_NAME])
print 'time', time() - st
#print SetWallpaper('%s/%s' % (ROOT_PATH, 'images_chache/1.png'))





