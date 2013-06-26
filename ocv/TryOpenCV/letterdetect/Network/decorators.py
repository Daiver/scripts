import time

def timecalcdec(fn):
    def timecalc(*args, **kwargs):
        st = time.time()
        res = fn(*args, **kwargs)
        print fn.__name__ + '\'s time', time.time() - st
        return res
    return timecalc

