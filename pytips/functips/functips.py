class tail_recursion(object):
    "Can call other methods inside..."
    def __init__(self, func):
        self.func = func

    def __call__(self, *args, **kwargs):
        result = self.func(*args, **kwargs)
        while callable(result): result = result()
        return result

    def call(self, *args, **kwargs):
        return lambda: self.func(*args, **kwargs)


def partitionToParts(predicate, parts, seq):
    partsdict = {x[0] : x[1] for x in parts}
    res = {x : [] for x in partsdict}
    for value in seq:
        key = partsdict[predicate(value)]
        res[key].append(value)
    return res

def partition(predicate, seq):
    res = partitionToParts(predicate, ((0, False), (1, True)), seq)
    return [res[0], res[1]]
