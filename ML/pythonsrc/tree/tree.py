class decisionnode:
    def __init__(self, col=-1, value=None, results=None, tb=None, fb=None):
        self.col = col
        self.value = value
        self.results = results
        self.tb = tb
        self.fb = fb
if __name__ == '__main__':
    data = [[ex for ex in s.split('\t')] for s in open('data')]
    print(data)
