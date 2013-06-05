def partitionToParts(predicate, parts, seq):
    partsdict = {x[0] : x[1] for x in parts}
    res = {}
    for value in seq:
        key = partsdict[predicate(value)]
        if not key in res: res[key] = []
        res[key].append(value)
    return res

def partition(predicate, seq):
    res = partitionToParts(predicate, ((0, False), (1, True)), seq)
    return [res[0], res[1]]
