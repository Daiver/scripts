
from random import random

def f(p):
    return p[0]*2 + p[1]*3 + p[2]*p[5] - 5*p[3]*p[4]

def fitness(p):
    return f(p) - 1009

def mutate(p):
    res = p[:]
    mut_index = int(random()*len(p))
    res[mut_index] *= (1 - 2*random())
    mut_index = int(random()*len(p))
    res[mut_index] += (1 - 2*random())
    return res

def cross(p1, p2):
    res = p1[:]
    res[len(p1)/2:] = p2[len(p2)/2:]
    return res

def gen_alg(p):
    best_err = abs(fitness(p))
    max_pop = 1000
    #pop = [mutate(p) for i in xrange(max_pop)]
    j = 0
    pop = [p for i in xrange(max_pop)]
    while abs(fitness(pop[0])) > 0.000001:
        j += 1
        pop = [mutate(p) if random() > 0.5 else p for p in pop] 
        parents = pop[:max_pop/2]
        pop = []
        for i in xrange(max_pop):
            pop.append(
                cross(parents[int(random()*len(parents))]
                , parents[int(random()*len(parents))])
            )
        pop.sort(key=lambda x:abs(fitness(x)))
        #for p in pop:print p, fitness(p)
        #raw_input()
    return j, pop[0]

if __name__ == '__main__':
    i, p = gen_alg([1, 1, 1, 1, 1, 1])
    print('RES')
    print i, p, f(p)

