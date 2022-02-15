# activations are rows
# weights are columns


from numpy import *

def sigmoid(x):
	return 1/(1+exp(-x))

def sigmoid_derivative(x):
    # sigmoid'(x) = sigmoid(x)*(1-sigmoid(x))
	return x*(1-x)

# Inputs and outputs
x = array([[0,0,0],
            [0,0,1],
            [0,1,0],
            [0,1,1],
            [1,0,0],
            [1,0,1],
            [1,1,0],
            [1,1,1]])
                
y = array([[0,0],
			[0,0],
			[0,0],
			[1,1],
			[0,0],
			[1,1],
			[1,1],
			[1,1]])



random.seed(1)


# randomly initialize our weights with mean 0
w0 = 2*random.random((3,4)) - 1
w1 = 2*random.random((4,4)) - 1
w2 = 2*random.random((4,2)) - 1

b0 = 2*random.random((4)) - 1
b1 = 2*random.random((4)) - 1
b2 = 2*random.random((2)) - 1


# for j in range(60000):

# Feed forward
a0 = x
a1 = sigmoid(dot(a0,w0)+b0)
a2 = sigmoid(dot(a1,w1)+b1)
a3 = sigmoid(dot(a2,w2)+b2)

if (j% 10000) == 0:
    print( "Error:" + str(mean(abs(y-a3))))

# dc/dw1 = dc/da2 da2/dz2 dz2/da1 da1/dz1 dz1/dw1

# Backpropagation and Gradient Descent
d2 = (a3-y) * a3*(1-a3)
w2 -= dot(a2.T, d2)
b2 -= dot(ones((d2.T.shape)), d2)[0,:]

d1 = dot(d2, w2.T) * a2*(1-a2)
w1 -= dot(a1.T, d1)
b1 -= dot(ones((d1.T.shape)), d1)[0,:]

d0 = dot(d1, w1.T) * a1*(1-a1)
w0 -= dot(a0.T, d0)
b0 -= dot(ones((d0.T.shape)), d0)[0,:]



# set_printoptions(precision=3)
# set_printoptions(suppress=True)

# print(a3)
