
FIND_SUC = 1
FIND_FAIL = 0
FIND_PART = 2

class Node:
    def __init__(self, value=None, key=None):
        self.value = value
        self.key = key
        self.childs = {}

    def Append(self, key, value, depth=0):
        self.childs[key[depth]] = node = Node()#BAD BAD BAD!!!11111
        if depth == len(key) - 1:
            node.key = key
            node.value = value
            return True
        node.Append(key, value, depth + 1)
        
    def __str__(self, additional=''):
        res = '%s:%s' % (str(self.key), str(self.value))
        for k, v in self.childs.iteritems():
            res += '\n%s%s->%s' % (additional, k, v.__str__(additional + '   '))
        return res
        

    def Add(self, key, value, depth=0):
        if depth >= len(key): return False
        node, depth, res = self.Find(key, depth)
        if res == FIND_SUC: return False
        
        node.Append(key, value, depth )
        

    def Find(self, key, depth=0):
        if self.key == key:
            return self, depth, FIND_SUC        
        if (depth >= len(key)):
            return self, depth, FIND_FAIL
        
        if key[depth] in self.childs:
            return self.childs[key[depth]].Find(key, depth + 1)
        else:
            return self, depth, FIND_PART

class Tree:
    def __init__(self):
        self.root = Node()

    def __str__(self):
        return str(self.root)

    def Find(self, key):
        node, d, res = self.root.Find(key)
        return node, res

    def Add(self, key, value):
        self.root.Add(key, value)
'''
tree = Tree()
tree.Add('123', 424244)
tree.Add('124444', 2)
tree.Add('12g', 2)
print tree
'''
#print root.childs['1'].childs['2'].childs['3'].value
