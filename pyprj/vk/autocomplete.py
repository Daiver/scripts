
import pickle

def raw_complete(query, li):
    res = []
    if query == '': return res
    query = query.lower()
    for j in xrange(len(li)):
        i = li[j].lower().find(query)
        if i > -1:
            res.append(j)
    return res

class AutoCompleter:
    
    def __init__(self):
        pass

'''
a = [
        'Hi guys',
        'Lo hi and Me',
        'nobody helps me'
    ]

print rawcomplete('HI', a)
'''
