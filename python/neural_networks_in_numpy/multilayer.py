
# Rewrite to clarify the backpropagation algorithm section

import numpy as np

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

layers = [(3,5),(5,4),(4,4),(4,1)]



def sigmoid(x):
	return 1/(1+np.exp(-x))


np.random.seed(1)

# randomly initialize our weights with mean 0
w = []
for layer in layers:
    w.append( 2*np.random.random(layer) - 1 )

for j in range(60000):

    # Activations and backpropagation temporary values
    a = []
    bp = []

	# Feed forward through layers
    a.append( X )
    for i,v in enumerate(w):
        a.append( sigmoid(np.dot(a[i],w[i])) )
        
    if (j% 10000) == 0:
        print( "Error:" + str(np.mean(np.abs(y-a[len(a)-1]))))

    # Backpropagation
    cost = y - a[len(a)-1]
    bp.insert(0, cost*a[len(a)-1]*(1-a[len(a)-1]) )

    for i in range(len(a)-2,0,-1):
        bp.insert(0, (np.dot(bp[0], w[i].T)) * a[i]*(1-a[i]) )

    for i in range(len(a)-2, -1, -1):
        w[i] += np.dot(a[i].T, bp[i])




np.set_printoptions(precision=3)
np.set_printoptions(suppress=True)

print(a[len(a)-1])
