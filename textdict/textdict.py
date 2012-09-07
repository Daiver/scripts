
import os

from prefixtree import Tree

def xor(a, b):
    return (a and not b) or (not a and b)

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
 
'''
special_chars = [
        '!', '<', '>', '.', ',', '@', '#', '$', '%', ':', ';', '(', ')',
        '*', '/', '+', '-', '{', '}', '[', ']', '=', '==', '+=', '-=', '*=', '/=',
        '!='
    ]
'''
space_chars = ['\n', ' ', '\t', '.', ',', '(', ')', '{', '}', '[', ']']

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

def completeTreet(dct):
    tree = Tree()
    for k, v in dct.iteritems():
        if k != '':
            #print k, v
            tree.Add(k, v)
            #print tree
    return tree

path = 'linux/arch'

files = treeDir(path)

dct = {}
for f in files:
    print f
    for x in open(f):
        dct = getDict(x,dct)

tree = completeTreet(dct)

i = 0
for k, v in dct.iteritems():
    res = tree.Find(k)
    if res[1] == 0:
        i += 1
#print i
#print tree

com = '1111'

while com != '':
    com = raw_input('>')
    st, res = tree.Find(com)
    print str(st[-1])
    print len(st)
