class decisionnode:
    def __init__(self, col=-1, value=None, results=None, tb=None, fb=None):
        self.col = col
        self.value = value
        self.results = results
        self.tb = tb
        self.fb = fb

def divideset(rows,column,value):
    split_function=None
    if isinstance(value,int) or isinstance(value,float):
        split_function=lambda row:row[column]>=value
    else:
        split_function=lambda row:row[column]==value
    set1=[row for row in rows if split_function(row)]
    set2=[row for row in rows if not split_function(row)]
    return (set1,set2)

def uniquecounts(rows):
    results={}
    for row in rows:
        r=row[len(row)-1]
        if r not in results: results[r]=0
        results[r]+=1
    return results

def giniimpurity(rows):
    total=len(rows)
    counts=uniquecounts(rows)
    imp=0
    for k1 in counts:
        p1=float(counts[k1])/total
        for k2 in counts:
            if k1==k2: continue
            p2=float(counts[k2])/total
            imp+=p1*p2
    return imp

def entropy(rows):
    from math import log
    log2=lambda x:log(x)/log(2)
    results=uniquecounts(rows)
    ent=0.0
    for r in results.keys( ):
        p=float(results[r])/len(rows)
        ent=ent-p*log2(p)
    return ent

def make_data_valid(data):
    return [[str(x) if i != 3 else float(x) for i, x in enumerate(row) ] for row in data]

if __name__ == '__main__':
    data = [[ex for ex in s.split('\t')] for s in open('data')]
    #print(divideset(make_data_valid(data), 2, 'yes')[0])
    #print(divideset(make_data_valid(data), 2, 'yes')[1])
    print(entropy(make_data_valid(data)))
