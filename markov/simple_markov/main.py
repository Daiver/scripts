import sys

def make_markov(text):
    res = {}
    text = text.split(' ')
    for i in xrange(1, len(text) - 1):
        if (text[i - 1], text[i]) not in res: res[(text[i - 1], text[i])] = []
        res[(text[i - 1], text[i])].append(text[i + 1])
    return res

if __name__ == '__main__':
    if len(sys.argv) > 1:
        text = ' '.join(open(sys.argv[1]).read().split('\n'))
        print(make_markov(text))
    else:
        print('NO')
