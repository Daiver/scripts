import numpy as np

#observations = ('normal', 'cold', 'dizzy')
#observations_seq = (0, 1, 2)
start_prob = np.array([
    [0.526],
    [0.474],
])
transition_probability = np.array([
    [0.969, 0.029],
    [0.063, 0.935]
])

emission_prob = [
    [0.005, 0.604],
    [0.775, 0.277],
    [0.220, 0.119],
]

def make_obs(obs):
    res = np.zeros((len(states), len(states)), dtype=np.float)
    for i in xrange(len(emission_prob[obs])):
        res[i, i] = emission_prob[obs][i]
    return res

def forward_backward(obs, transition_probability, start_prob):
    end = -1
    def normalize(x): return x / sum(x.reshape(-1))
    f = [start_prob]
    for x in obs:
        f.append(normalize(
                np.dot(np.dot(x, transition_probability.transpose()), f[end])
            ))
        #f.append(normalize(new_f))
    b = [np.array([[1.0] for _ in states])]
    for x in reversed(obs):
        b.append(normalize(
                np.dot(np.dot(transition_probability, x), b[end])
            ))
        #b.append(normalize(new_b))
    gamma = [normalize(i_f * i_b) for i_f, i_b in zip(f, reversed(b))]
    return f, b, gamma

def find_max_state(state_matrix):
    max_index = -1
    max_value = 0.0
    for i, x in enumerate(state_matrix):
        if x > max_value:
            max_value = x
            max_index = i
    return max_index

#print map(make_obs, observations_seq)o
states = {'St1':0, 'St2':1}
observations = {'a':0, 'b':1, 'c':2}
obs_seq = []
res = []
with open('hmmdata') as f:
    f.readline()
    for s in f:
        tmp = s.split()
        obs_seq.append(observations[tmp[2]])
        res.append(states[tmp[1]])

ans = forward_backward(map(make_obs, obs_seq), transition_probability, start_prob)[2]

fp = 0; tp = 0
for i, x in enumerate(map(find_max_state, ans[1:])):
    if x == res[i]: tp +=1
    else: fp += 1
print tp, fp
