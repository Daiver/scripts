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
    et2=[row for row in rows if not split_function(row)]
    return (set1,set2)

def make_data_valid(data):
    return [[str(x) if i != 3 else float(x) for i, x in enumerate(row) ] for row in data]

if __name__ == '__main__':
    data = [[ex for ex in s.split('\t')] for s in open('data')]
    print(make_data_valid(data))
