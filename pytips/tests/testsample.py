import unittest

def f(n):
    return n**2

class Test(unittest.TestCase):
    def test_run_once(self):
        self.assertEqual(f(2), 4)
        self.assertEqual(f(3), 9)

class Test2(unittest.TestCase):
    def test_run_once(self):
        self.assertEqual(f(5), 25)
        self.assertEqual(f(6), 9)


if __name__ == "__main__":
    unittest.main()


