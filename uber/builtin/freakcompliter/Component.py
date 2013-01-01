# -*- coding: utf-8 -*-

import os

import prefixtree
from prefixtree import Tree

from component import Component

from Queue import Queue 

def treeDir(fullPath):
    list = os.listdir(fullPath)
    res = []
    for path in list:
        link = os.path.join(fullPath, path)
        if os.path.isfile(link):
            res.append(os.path.join(fullPath, path))#print 'FILE:', path
        else:
            if os.path.isdir(link):
                for x in treeDir(link):
                    res.append(x)
    return res
 

space_chars = ['\n', ' ', '\t', '.', ',', '(', ')', '{', '}', '[', ']',
               '-', '=', ':', '==']

def wordfromtext(raw_text, index=0):
    i = index
    while (i < len(raw_text)) and raw_text[i] in space_chars:
        i += 1
    res = ''

    while (i < len(raw_text)) and (raw_text[i] not in space_chars):
        res += raw_text[i]
        i += 1

    return res, i
        
def wordsList(raw_text):
    res = []
    txt,i = wordfromtext(raw_text)
    
    while txt != '':
        res.append(txt)
        txt,i = wordfromtext(raw_text, i)
        
    return res

def getDict(raw_text, dct={}):
    #dct = {}
    txt,i = wordfromtext(raw_text)

    while txt != '':
        if txt not in dct:
            dct[txt] = 0
        dct[txt] += 1
        txt,i = wordfromtext(raw_text, i)

    #dct.sort()
    return dct

def DictFromFiles(path, dct = {}):
    files = treeDir(path)

    for f in files:
        for x in open(f):
            dct = getDict(x,dct)
    return dct

def completeTree(dct):
    tree = Tree()
    for k, v in dct.iteritems():
        if k != '':
            #print k, v
            tree.Add(k, v)
            #print tree
    return tree

class Compliter:
    def __init__(self):
        self.dct = {}
        self.tree = None

    def FromFiles(self, path):
        self.dct = DictFromFiles(path, self.dct)
        self.tree = completeTree(self.dct)

    def FromText(self, text):
        self.dct = getDict(text, self.dct)
        self.tree = completeTree(self.dct)

    def Reset(self):
        self.dct = {}
        self.tree = None

    def Completelist(self, txt):
        
        res = []
        stack, ans = self.tree.Find(txt)
        
        if (ans in [0, 1]) and len(stack) > 1:
            towalk = Queue()
            towalk.put(stack[-1])
            
            while not towalk.empty():
                node = towalk.get()                
                for k, v in node.childs.iteritems():
                    towalk.put(v)
                    if v.value:
                        res.append(v)
        res.sort(key=lambda x: -x.value)
        res = [x.key for x in res]
        #for x in res:
        #    print x
        return res

class freakcompliter(Component):
    def __init__(self):
        Component.__init__(self)
        self.compliterclass = Compliter

    def Register(self, cc):
        #com = Compliter()
        #com.FromFiles('../')
        #print com.Completelist('re')
        return None

def GetComponent():
    return freakcompliter()

    
