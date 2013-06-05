from functips import *
import unittest

from random import random


class PartitionTest(unittest.TestCase):
    def test_simple1(self):
        res = partition(lambda x: x % 2 == 0, xrange(10))
        self.assertEqual(res[1], [0, 2, 4, 6, 8])
        self.assertEqual(res[0], [1, 3, 5, 7, 9])

    def test_simple2(self):
        for j in xrange(1000):
            border = int(500 - random()*1000)
            f = lambda x: x > border
            seq_len = 100
            seq = [int(random()*1000 - 500) for x in xrange(seq_len)]
            tr, fl = 0, 0
            for i in seq:
                if f(i):
                    tr += 1
                else:
                    fl += 1
            ans = partition(f, seq)
            self.assertEqual(len(ans[0]), fl)
            self.assertEqual(len(ans[1]), tr)


class RecursionTest(unittest.TestCase):
    def N_sum_simple(self, N):
        @tail_recursion
        def sum_natural(x, result=0):
            if x == 0:
                return result
            else:
                return sum_natural.call(x - 1, result + x)

        def sum_sum(n):
            res = 0
            for i in xrange(n+1):res += i
            return res
        self.assertEqual(sum_natural(N), sum_sum(N))

    def test_sum_100(self):
        self.N_sum_simple(100)

    def test_sum_10000(self):
        self.N_sum_simple(10000)


if __name__ == '__main__':
    unittest.main()
