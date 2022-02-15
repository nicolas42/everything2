# activations are rows
# weights are columns

import numpy as np
np.random.seed(42)


x = np.array([[0,0,0],
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
			[1],
            ])

layers = [ (3,5), (5,5), (5,1) ]


def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    # sigmoid'(x) = sigmoid(x)*(1-sigmoid(x))
    return x * (1 - x)

w = []
b = []
for shape in layers:
    w.append(2 * np.random.random(shape) - 1)
    b.append(2 * np.random.random((1,shape[1])) - 1)

for iteration in range(10000):

    # activations
    a = []
    a.append(x)
    for i,_ in enumerate(layers):
        a.append( sigmoid(np.dot(a[i], w[i]) + b[i]) )

    # the network feeds forward for neurons with a dot product of activations
    # and synaptic weights plus bias and a nonlinear activation function
    # cost is defined as the square of the difference between the output
    # and the correct output

    # z0 = w0 a0 + b0
    # a1 = sigma(z0)
    # z1 = w1 a1 + b1
    # a2 = sigma(z1)
    
    # c = sum(a2-y)^2

    # we can calculate the derivative of the cost with respect to the weights and biases
    # in concert they give the gradient - the direction in the weight,bias space 
    # which will maximize the error.  We go in the opposite direction



    # Back propagation

    # The gradients with respect to the different layers
    # dc/dw2 = dc/da3  da3/dz3   dz3/dw2
    # dc/dw1 = dc/da3  da3/dz3   dz3/da2 da2/dz2   dz2/dw1
    # dc/dw0 = dc/da3  da3/dz3   dz3/da2 da2/dz2   dz2/da1 da1/dz1   dz1/dw0

    # Calculate these derivatives first
    # d[2] = dc/da3  da3/dz3   
    # d[1] = dc/da3  da3/dz3   dz3/da2 da2/dz2
    # d[0] = dc/da3  da3/dz3   dz3/da2 da2/dz2   dz2/da1 da1/dz1

    # so then the gradients for the different layers are these
    # dc/dw2 = d[2] dz3/dw2
    # dc/dw1 = d[1] dz2/dw1
    # dc/dw0 = d[0] dz1/dw0


    # generate in reverse order by inserting items at the beginning
    d = [] 
    cost = a[-1]-y
    
    d.insert(0, cost * sigmoid_derivative(a[len(a)-1]) ) # dc/da3 * da3/dz3
    for i in range(len(a)-2, 0, -1): # i=[len(a)-2..1]
        # d[0] is most recent derivative to be inserted
        d.insert(0, (np.dot(d[0], w[i].T)) * sigmoid_derivative(a[i]) )

    # d2 = cost * sigmoid_derivative(a[3])
    # d1 = np.dot(d2, w[2].T ) * sigmoid_derivative( a[2] )
    # d0 = np.dot( d1, w[1].T ) * sigmoid_derivative( a[1] )
    # d = []; d.append(d0); d.append(d1); d.append(d2)

    # gradient descent
    for i,_ in enumerate(w):
        w[i] -= np.dot( a[i].T, d[i] )
        b[i] -= np.dot( np.ones( ( d[i].T.shape ) ), d[i] )[0,:]

    if ( iteration % 1000 ) == 0: 
        print(np.dot(cost.T,cost))

