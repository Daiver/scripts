
class recursion(object):
    "Can call other methods inside..."
    def __init__(self, func):
        self.func = func

    def __call__(self, *args, **kwargs):
        result = self.func(*args, **kwargs)
        while callable(result): result = result()
        return result

    def call(self, *args, **kwargs):
        return lambda: self.func(*args, **kwargs)

if __name__ == '__main__':
    import time
    @recursion
    def sum_natural(x, result=0):
        if x == 0:
            return result
        else:
            return sum_natural.call(x - 1, result + x)

    def test(n):
        res = 0
        for i in xrange(n):res += 1
        return res

    st = time.time()
    print(sum_natural(1000000))
    print('Tail %s' % str(time.time() - st))
    st = time.time()
    print(test(1000000))
    print('Xrange %s' % str(time.time() - st))
