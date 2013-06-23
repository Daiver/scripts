import numpy as np

with open('mat') as f:
    print np.array([map(int, st.split(' ')) for st in f])[1, 2]
