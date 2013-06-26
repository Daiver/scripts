
import pybrain
import pickle

def ListFromDir(directory):
    return [directory + '/' + i for i in os.listdir(directory)]

def NameFromDict(dct):
    return 's_' + str(dct['size'][0]) + '_' + str(dct['size'][1]) + '_p' + str(dct['poscross']) + '_n' + str(dct['negcross'])

def WriteDict(dct):
    f = open(NameFromDict(dct) + '.txt', 'w')
    f.write(str(dct) + '\n')
    f.close()

def WriteNet(dct):
    WriteDict(dct)
    f = open(NameFromDict(dct), 'w')
    pickle.dump(dct['net'], f)
    f.close()


negdatasetprocs = [100, 500, 1000, 5000, 15000]
posdatasetprocs = [100, 500, 1000, 5000, 15000]

sizesX = [5, 10, 20, 40]
sizesY = [5, 10, 20, 40]

hiddenlayers = [5, 10, 100, 500]

trainepochs = [1, 2, 5, 10]

pure_neg = ListFromDir('images/neg')
new_neg = ListFromDir('images/new_neg')

mix_neg = pure_neg[:]
for x in new_neg: mix_neg.append(x)
print 'len of mix_neg:', len(mix_neg)

pos = ListFromDir('images/pos')
print 'len of pos:', len(pos)

poscrossvalidation = pos[15000 : 20000]
negcrossvalidation = mix_neg[15000 : 20000]

for negdatasetsize in negdatasetprocs:
    for posdatasetsize in posdatasetprocs:
        for sizex in sizesX:
            for sizey in sizesY:
                size = (sizex, sizey)
                
                for hiddensize in hiddenlayers:
                    for trainepoch in trainepochs:
                        pass
                    
                    
