from matrix import *
from math import *

# --------------------------------
#
# online_slam - retains all landmarks but only most recent robot pose
#

def online_slam(data, N, num_landmarks, motion_noise, measurement_noise, world_size):
    #
    #
    # Enter your code here!
    #
    #
    dim = 2 + 2*num_landmarks
    Omega = matrix()
    Omega.zero(dim, dim)
    
    Xi = matrix()
    Xi.zero(dim, 1)    
    
    Omega.value[0][0] = 1.0
    Omega.value[1][1] = 1.0
    Xi.value[0][0] = world_size / 2.0
    Xi.value[1][0] = world_size / 2.0
    #Xi.show('xi')
    
    for sample in data:
        measurement = sample[0]
        motion      = sample[1]
        
        for i in range(len(measurement)):
    
            # m is the index of the landmark coordinate in the matrix/vector
            m = 2 * (1 + measurement[i][0])
            # update the information maxtrix/vector based on the measurement
            for b in range(2):
                Omega.value[b][b]     +=  1.0 / measurement_noise
                Omega.value[m+b][m+b] +=  1.0 / measurement_noise
                Omega.value[b][m+b]   += -1.0 / measurement_noise
                Omega.value[m+b][b]   += -1.0 / measurement_noise
                Xi.value[b][0]        += -measurement[i][1+b] / measurement_noise
                Xi.value[m+b][0]      +=  measurement[i][1+b] / measurement_noise

        
        #lst = [i for i in xrange(dim+2) if i not in [2, 3]]
        lst = [0, 1] + range(4, dim + 2)
        Omega = Omega.expand(dim + 2, dim + 2, lst, lst)
        Xi = Xi.expand(dim + 2, 1, lst, [0])
        
        for b in xrange(4):
            Omega.value[b][b] += 1.0/motion_noise
        
        for b in range(2):
            Omega.value[b  ][b+2] += -1.0 / motion_noise
            Omega.value[b+2][b  ] += -1.0 / motion_noise
            Xi.value[b  ][0]      += -motion[b] / motion_noise
            Xi.value[b+2][0]      +=  motion[b] / motion_noise
        
        lst = range(2, len(Omega.value))#[i for i in xrange(2, dim+2)]
        A = Omega.take([0, 1], lst)        
        B = Omega.take([0, 1])
        C = Xi.take([0, 1], [0])
        
        tOmega = Omega.take(lst)
        tXi = Xi.take(lst, [0])
        
        #print 'a shape', A.transpose().dimx, A.transpose().dimy
        #print 'b shape', B.inverse().dimx, B.inverse().dimy
        #tmp = A * B.inverse()
        #Omega.show('om')
        #Xi.show('xi')
        Omega = tOmega - A.transpose() * B.inverse() * A
        Xi = tXi - A.transpose() * B.inverse() * C
        #Omega.show('om')
        #Xi.show('xi')
        
    mu = Omega.inverse() * Xi
    return mu, Omega # make sure you return both of these matrices to be marked correct.


