
# https://iamtrask.github.io/2015/07/12/basic-python-network/

# python -i twolayers.py
# run in interactive mode

import numpy as np

def nonlin(x):
	return 1/(1+np.exp(-x))

# Inputs and outputs
X = np.array([[0,0,1],
            [0,1,1],
            [1,0,1],
            [1,1,1]])
                
y = np.array([[0],
			[1],
			[1],
			[0]])



np.random.seed(1)

# randomly initialize our weights with mean 0
syn0 = 2*np.random.random((3,4)) - 1
syn1 = 2*np.random.random((4,1)) - 1


for j in range(60000):

	# Feed forward through layers 0, 1, and 2
    l0 = X
    l1 = nonlin(np.dot(l0,syn0))
    l2 = nonlin(np.dot(l1,syn1))

    # how much did we miss the target value?
    l2_error = y - l2
    
    if (j% 10000) == 0:
        print( "Error:" + str(np.mean(np.abs(l2_error))))
        
    # in what direction is the target value?
    # were we really sure? if so, don't change too much.
    l2_delta = l2_error*l2*(1-l2)

    # how much did each l1 value contribute to the l2 error (according to the weights)?
    l1_error = np.dot(l2_delta, syn1.T)
    
    # in what direction is the target l1?
    # were we really sure? if so, don't change too much.
    l1_delta = l1_error * l1*(1-l1)

    syn1 += np.dot(l1.T, l2_delta)
    syn0 += np.dot(l0.T, l1_delta)



np.set_printoptions(precision=3)
np.set_printoptions(suppress=True)

print(l2)
