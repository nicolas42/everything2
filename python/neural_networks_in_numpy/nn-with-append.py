
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
w = []
w.append( 2*np.random.random((3,4)) - 1 )
w.append( 2*np.random.random((4,4)) - 1 )
w.append( 2*np.random.random((4,1)) - 1 )


for j in range(60000):

    a = []
    bp = []

	# Feed forward through layers
    a.append( X )
    a.append( nonlin(np.dot(a[0],w[0])) )
    a.append( nonlin(np.dot(a[1],w[1])) )
    a.append( nonlin(np.dot(a[2],w[2])) )

    if (j% 10000) == 0:
        print( "Error:" + str(np.mean(np.abs(y-a[3]))))

    # Backpropagation
    cost = y - a[3]
    bp.insert(0, cost*a[3]*(1-a[3]) )
    bp.insert(0, (np.dot(bp[0], w[2].T)) * a[2]*(1-a[2]) )
    bp.insert(0, (np.dot(bp[0], w[1].T)) * a[1]*(1-a[1]) )

    w[2] += np.dot(a[2].T, bp[2])
    w[1] += np.dot(a[1].T, bp[1])
    w[0] += np.dot(a[0].T, bp[0])

np.set_printoptions(precision=3)
np.set_printoptions(suppress=True)

print(a[3])
