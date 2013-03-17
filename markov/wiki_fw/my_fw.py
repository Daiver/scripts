import numpy as np

transition_probability = np.array([
        [0.7, 0.3],
        [0.3, 0.7]
    ])

observations = [
    np.array([[0.9, 0.0], [0.0, 0.2]]),
    np.array([[0.9, 0.0], [0.0, 0.2]]),
    np.array([[0.1, 0.0], [0.0, 0.8]]),
    np.array([[0.9, 0.0], [0.0, 0.2]]),
    np.array([[0.9, 0.0], [0.0, 0.2]]),
]

def fw(obs, transition_probability):
    normalize = lambda x: x / sum(x.reshape(-1))
    f = [np.array([[0.5], [0.5]])]
    for x in obs:
        new_f = np.dot(
            np.dot(x, transition_probability.transpose()),
            f[-1]
        )
        new_f = normalize(new_f)
        f.append(new_f)
    b = [np.array([[1.0], [1.0]])]
    for x in reversed(obs):
        new_b = np.dot(np.dot(transition_probability, x), b[-1])
        new_b = normalize(new_b)
        b.append(new_b)
    gamma = [normalize(i_f * i_b) for i_f, i_b in zip(f, reversed(b))]
    return f, b, gamma

for sample in fw(observations, transition_probability):
    print '===================='
    for line in sample:
        print line
