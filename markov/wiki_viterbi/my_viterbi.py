states = ('healthy', 'fever')
#observation = ('cold', 'normal', 'dizzy')
start = {'healthy' : 0.6, 'fever' : 0.4}

trans = {
    'healthy' : {'healthy' : 0.7, 'fever' : 0.3},
    'fever' : {'healthy' : 0.4, 'fever' : 0.6},
}

emission = {
        'healthy' : {'cold' : 0.4, 'normal' : 0.5, 'dizzy' : 0.1},
        'fever' :  {'cold' : 0.3, 'normal' : 0.1, 'dizzy' : 0.6},
}

obs_seq = ('normal', 'cold', 'dizzy')

def gen_path(obs):
    V = [{}]
    path = {}

    for s in states:
        V[0][s] = start[s] * emission[s][obs[0]]
        path[s] = [s]

    for y in obs[1:]:
        V.append({})
        new_path = {}
        for s in states:
            prob, st = max((V[-2][old_st] * trans[old_st][s] * emission[s][y], old_st) for old_st in states)
            V[-1][s] = prob
            new_path[s] = path[st] + [s]
        path = new_path
    print V
    prob, state = max([(V[- 1][s], s) for s in states])
    return prob, path[state]
    #best_st = max(V[-1])
    #return V[-1][best_st], path[best_st]

print gen_path(obs_seq)
