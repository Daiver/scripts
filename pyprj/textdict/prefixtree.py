
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
    
    def Add(self, key, value):
       
       stack, res = self.Find(key)
       if res == FIND_SUC:
           stack[-1].value = value
           return
        
       depth = len(stack) - 1
       if depth == len(key):
           stack[-1].value = value
           stack[-1].key = key
           return
       stack[-1].Append(key, value, len(stack) - 1)

    def Find(self, key, stack=None): 
        if not stack: stack = []
        stack.append(self)
        depth = len(stack) - 1
        if self.key == key:
            return stack, FIND_SUC
        if (depth >= len(key)):
            return stack, FIND_FAIL
        
        if key[depth] in self.childs:
            return self.childs[key[depth]].Find(key, stack)

        if depth == 0:
            return stack, FIND_FAIL
        
        return stack, FIND_PART
'''
    def Add(self, key, value, depth=0):
        if depth >= len(key): return False
        stack, res = self.Find(key, depth)
        if res == FIND_SUC: return False
        node = stack[-1]
        node.Append(key, value, len(stack) - 1)

    def Find(self, key, depth=0):
        if self.key == key:
            return self, depth, FIND_SUC        
        if (depth >= len(key)):
            return self, depth, FIND_FAIL
        
        if key[depth] in self.childs:
            return self.childs[key[depth]].Find(key, depth + 1)
        else:
            return self, depth, FIND_PART
'''

class Tree:
    def __init__(self):
        self.root = Node()

    def __str__(self):
        return str(self.root)

    def Find(self, key):
        #s res = 
        return self.root.Find(key)

    def Add(self, key, value):
        self.root.Add(key, value)

'''
tree = Tree()

tree.Add('124444', 2)
tree.Add('126', 2)
tree.Add('g2', 2)
tree.Add('g', 2)

print tree
'''
