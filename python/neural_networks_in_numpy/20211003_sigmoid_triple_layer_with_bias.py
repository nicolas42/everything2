# activations are rows
# weights are columns


import numpy as np
np.random.seed(42)

def relu(x):
    return np.maximum(0,x)

def relu_derivative(x):
    return (x > 0) * 1.0

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def da_dz(x):
    # sigmoid'(x) = sigmoid(x)*(1-sigmoid(x))
    return x * (1 - x)


# Inputs and outputs
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



w = []
b = []
for shape in layers:
    w.append(2 * np.random.random(shape) - 1)
    b.append(2 * np.random.random((1,shape[1])) - 1)


# for j in range(60000):

# calculate the activation layers
# first layer is input activations.  the last layer is the output activations.
a = [[],[],[],[]]
a[0] = x
a[1] = sigmoid(np.dot(a[0], w[0]) + b[0])
a[2] = sigmoid(np.dot(a[1], w[1]) + b[1])
a[3] = sigmoid(np.dot(a[2], w[2]) + b[2])

# if (j% 10000) == 0:
#     print( "Error:" + str(np.mean(np.abs(y-a[3]))))

# Backpropagation and gradient descent
# ------------------------------------------------

# The gradients with respect to the different layers
# dc/dw2 = dc/da3 da3/dz3   dz3/dw2
# dc/dw1 = dc/da3 da3/dz3   dz3/da2 da2/dz2   dz2/dw1
# dc/dw0 = dc/da3 da3/dz3   dz3/da2 da2/dz2   dz2/da1 da1/dz1   dz1/dw0

# There are n derivatives of the form dz/da and dz/dw
# Since
# z = w0 a0 + w1 a1 + ... w_n a_n + b
# dz/da0 = w0
# dz/da1 = w1
# dz/dw0 = a0
# dz/dw1 = a1
# dz/db = 1
# and so on


# d[2]
# array([[ 0.069],
#        [ 0.066],
#        [ 0.069],
#        [-0.006],
#        [ 0.066],
#        [-0.005],
#        [-0.006],
#        [-0.005]])

# w[2].T
# array([[0.769, 0.502, 0.825, 0.603, 0.115]])

# so you get n copies of the derivative each
 

# dc/dz1 = dc/da3 da3/dz3   dz3/da2 da2/dz2   dz2/da1 da1/dz1
d = [[],[],[]]
dc_da = (a[3]-y)
# d[n] = dc/dz[n]
d[2] = dc_da * da_dz(a[3]) # dc/dz3
d[1] = np.dot( d[2], w[2].T ) * da_dz(a[2]) # dc/dz2
d[0] = np.dot( d[1], w[1].T ) * da_dz(a[1]) # dc/dz1

lr = 1 # learning rate
w[0] -= lr * np.dot(a[0].T, d[0])
w[1] -= lr * np.dot(a[1].T, d[1])
w[2] -= lr * np.dot(a[2].T, d[2])

b[0] -= lr * np.dot(np.ones((d[0].T.shape)), d[0])[0,:]
b[1] -= lr * np.dot(np.ones((d[1].T.shape)), d[1])[0,:]
b[2] -= lr * np.dot(np.ones((d[2].T.shape)), d[2])[0,:]



np.set_printoptions(precision=3)
np.set_printoptions(suppress=True)

print(a[3])
