"""
from https://iamtrask.github.io/2015/07/12/basic-python-network/

How to run python in interactive mode
# python -i twolayers.py
# run in interactive mode

The activations of the different layers are generated with a linear combination of the input data with the synaptic weights.
This occurs through the layers; the activations of the previous layer forming the input for the next.  The previous layer's 
activations are combined with the synaptic weights to determine the activations of the next layer.

The layer activations are set out in rows.  Each row corresponds to the activations of a particular layer for a particular input.
Consequently
"""


import numpy as np

def sigmoid(x):
	return 1/(1+np.exp(-x))

def D(x):
    return x*(1-x)

x = np.array([[0,0,1],
            [0,1,1],
            [1,0,1],
            [1,1,1]])
                
y = np.array([[0],
			[1],
			[1],
			[0]])

# randomly initialize our weights with mean 0
np.random.seed(1)
s1 = 2*np.random.random((3,4)) - 1
s2 = 2*np.random.random((4,1)) - 1

for j in range(60000):

    # feedfordward
    l0 = x
    l1 = sigmoid(np.dot(x,s1))
    l2 = sigmoid(np.dot(l1,s2))

    # back propagation
    err = (l2-y)
    s2 -= np.dot( l1.T, D(l2) * err )
    s1 -= np.dot( l0.T, D(l1) *  np.dot( D(l2) * err, s2.T ) )

    if (j% 10000) == 0:
        print( "Error:" + str(np.mean(np.abs(y - l2))))




# np.set_printoptions(precision=3)
# np.set_printoptions(suppress=True)

print(l2)
