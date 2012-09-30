# -*- coding: utf-8 -*-
import re

import os

import sys

import urllib2

from random import random

#from htmllib import HTMLParser

from time import time

import lxml.html

from commands import *

def MkDir(destdir, name):
    template = 'mkdir %s%s' % (destdir, name)
    getoutput(template)

def DownLoadFile(url, filename):
    try:
        open(filename, "w").write(urllib2.urlopen(url).read())
    except Exception as e:
        print 'error on url', url, 'with fname', filename, '\nerror:', e

def DownLoadImage(url, destdir):
    num_st_ind = url.rfind('/')
    fname = '%s%s' % (destdir, url[num_st_ind + 1:])
    DownLoadFile(url, fname)

def DownLoadEl(pageaddr, el, destdir):
    newdir = destdir + str(el['href'])
    MkDir(destdir, el['href'])
    f = open(newdir + '/' + str(el['number']) + '.txt', 'w')
    f.write(str(el['number']))
    f.close()
    for fname in el['photos']:
        DownLoadImage(pageaddr + '/' + fname, newdir + '/')
    

def GetElementsFromPage(pageaddr, elements):
    page = urllib2.urlopen(pageaddr)
    html = page.read()
    doc = lxml.html.document_fromstring(html)
    #ul chmo_list
    #txt1 = doc.xpath('/html/body/div/div/div/div')
    res = doc.cssselect('ul.chmo_list')# select chmo_list
    for li in res[0].cssselect('li'):
        el = {}
        for tag in li:#z is tag in element
            tagname = tag.tag
            #print tagname
            if tagname == 'a':
                #print tag.get('href')
                tmp = tag.get('href')
                lind = tmp.find('i')
                
                href = int(tmp[1:lind]) if lind  else int(tmp[1:])
                el['href'] = href
            
        elements[href] = el

    #p = re.compile(r"/upload/avtochmo/original/[a-z0-9_]+\.jpg")#/upload/avtochmo/original
    p = re.compile(r"/upload/avtochmo/original/[A-zА-я0-9_\.]+\.jpg")
    #[a-z][a-z0-9\._]
    for el in elements:
        page = urllib2.urlopen("http://autochmo.ru/%s" % el)
        html = page.read()
        photos = p.findall(html)
        elements[el]['photos'] = photos
        if len(photos) > 0:
            num_st_ind = photos[0].rfind('/')
            num_st_end = photos[0].find('_')
            number = photos[0][num_st_ind + 1: num_st_end]
            elements[el]['number'] = number
        else:
            elements[el]['number'] = None


pageaddr = "http://autochmo.ru"

destdir = '/home/kirill/fromavtochmo/'


for i in xrange(528, 745):
    start = time()
    addr = pageaddr if i == 0 else pageaddr + '/?page=' + str(i)
    print 'scan page', i, addr
    elements = {}
    GetElementsFromPage(addr, elements)
    print 'time:', time() - start
    print elements

    for k, el in elements.iteritems():
        DownLoadEl(pageaddr, el, destdir)

#DownLoadImage(pageaddr + 'upload/avtochmo/original/b787tm_20120929190912.jpg', destdir)
#MkDir(destdir, '12344')
print 'the end'
