from Input import *
from Neuron import *
from Link import *

class Network:
    def __init__(self, inputcount, outputvalues):        
        self.Neurons = [Neuron(x) for x in outputvalues]
        self.inputs = []
        for x in xrange(0, inputcount):
            inputneu = Input()

            for x in self.Neurons:
                link = Link(x)
                x.IncomingLinks.append(link)
                inputneu.OutgoingLinks.append(link)
            
            self.inputs.append(inputneu)

    def Study(self, Input, correct):
        rightneuron = max(self.Neurons, key=lambda x:x.Value==correct)
        #print rightneuron.Power, rightneuron.Value
        for i in xrange(0, len(rightneuron.IncomingLinks)):
            link = rightneuron.IncomingLinks[i]
            link.weight += + 0.5 * (Input[i] - link.weight)
            #print link.weight
    
    def Handle(self, Input):
        for i in xrange(0, len(self.inputs)):
            inputneu = self.inputs[i]

            for x in inputneu.OutgoingLinks:
                x.Neuron.Power += x.weight * Input[i]

        res = max(self.Neurons, key=lambda x:x.Power)

        for x in self.Neurons:
            x.Power = 0
        
        return res
network = Network(45*45, [0, 1, 2])
