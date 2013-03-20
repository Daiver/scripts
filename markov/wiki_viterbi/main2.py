states = ('St1', 'St2')
 
observations = ('a', 'b', 'c')
#observations = ('dizzy', 'cold', 'cold', 'dizzy')
 
start_probability = {'St1': 0.526, 'St2': 0.474}
 
transition_probability = {
   'St1' : {'St1': 0.969, 'St2': 0.029},
   'St2' : {'St1': 0.063, 'St2': 0.935},
   }
 
emission_probability = {
   'St1' : {'a': 0.005, 'b': 0.775, 'c': 0.220},
   'St2' : {'a': 0.604, 'b': 0.277, 'c': 0.119},
   }



def print_dptable(V):
    print "    ",
    for i in range(len(V)): print "%7d" % i,
    print
 
    for y in V[0].keys():
        print "%.5s: " % y,
        for t in range(len(V)):
            print "%.7s" % ("%f" % V[t][y]),
        print
 
def viterbi(obs, states, start_p, trans_p, emit_p):
    V = [{}]
    path = {}
 
    # Initialize base cases (t == 0)
    for y in states:
        V[0][y] = start_p[y] * emit_p[y][obs[0]]
        path[y] = [y]
 
    # Run Viterbi for t > 0
    for t in range(1,len(obs)):
        V.append({})
        newpath = {}
 
        for y in states:
            (prob, state) = max([(V[t-1][y0] * trans_p[y0][y] * emit_p[y][obs[t]], y0) for y0 in states])
            V[t][y] = prob
            newpath[y] = path[state] + [y]
 
        # Don't need to remember the old paths
        path = newpath
 
    print_dptable(V)
    (prob, state) = max([(V[len(obs) - 1][y], y) for y in states])
    return (prob, path[state])

def example():
    observations = []
    res = []
    with open('hmmdata') as f:
        f.readline()
        for s in f:
            tmp = s.split()[1:]
            res.append(tmp[0])
            observations.append(tmp[1])
    vi = viterbi(observations,
                   states,
                   start_probability,
                   transition_probability,
                   emission_probability)
    for i, x in enumerate(res):
        print x == vi[1][i]
print example()
