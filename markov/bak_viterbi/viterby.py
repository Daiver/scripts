states = ['health', 'fever']
observations = ['normal', 'cold', 'dizzy']

observations_seq = (2, 1, 1, 2)

trans = [
    [0.7, 0.3],
    [0.4, 0.6]
]

start_prob = [0.6, 0.4]
emission_probs = [
    [0.5, 0.4, 0.1],
    [0.1, 0.3, 0.6]
]

def viterbi(obs):
    V = [[]]
    path = []
    for i in xrange(len(states)):
        V[0].append(emission_probs[i][obs[0]] * start_prob[i])
        path.append([i])
    
    for i, x in enumerate(obs[1:]):
        new_path = []
        V.append([])
        for j, _ in enumerate(states):
            (prob, state) = max([ emission_probs[j][x] * trans[old][j] * V[-2][old], old] for old, _ in enumerate(states))
            V[-1].append(prob)
            new_path.append([state] + path[j])
        path = new_path

    (prob, state) = max([(V[len(obs) - 1][y], y) for y, _ in enumerate(states)])
    return prob, path[state]

print viterbi(observations_seq)
