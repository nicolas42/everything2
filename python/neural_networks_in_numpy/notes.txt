def relu(x):
    return np.maximum(0,x)


def relu_derivative(x):
    return (x > 0) * 1.0




# Rewrite to clarify the backpropagation algorithm section

import numpy as np

def nonlin(x):
	return 1/(1+np.exp(-x))

# Inputs and outputs
X = np.array([[0,0,0],
            [0,0,1],
            [0,1,0],
            [0,1,1],
            [1,0,0],
            [1,0,1],
            [1,1,0],
            [1,1,1]])
                
y = np.array([[0],
			[0],
			[0],
			[1],
			[0],
			[1],
			[1],
			[1]])



np.random.seed(1)

# randomly initialize our weights with mean 0
w1 = 2*np.random.random((3,4)) - 1
w2 = 2*np.random.random((4,4)) - 1
w3 = 2*np.random.random((4,1)) - 1


for j in range(60000):

	# Feed forward through layers
    a0 = X
    a1 = nonlin(np.dot(a0,w1))
    a2 = nonlin(np.dot(a1,w2))
    a3 = nonlin(np.dot(a2,w3))

    if (j% 10000) == 0:
        print( "Error:" + str(np.mean(np.abs(y-a3))))

    # Backpropagation
    cost = y - a3
    l3 = cost*a3*(1-a3)
    l2 = (np.dot(l3, w3.T)) * a2*(1-a2)
    l1 = (np.dot(l2, w2.T)) * a1*(1-a1)

    w3 += np.dot(a2.T, l3)
    w2 += np.dot(a1.T, l2)
    w1 += np.dot(a0.T, l1)



np.set_printoptions(precision=3)
np.set_printoptions(suppress=True)

print(a3)
