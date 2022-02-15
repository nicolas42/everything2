# numpy resize fill with zeroes
# slows a lot
np.lib.pad(syn0, ((0,1),(0,0)), 'constant', constant_values=(0))
# https://stackoverflow.com/questions/33256823/numpy-resize-array-filling-with-0/33256879



# Make input output function (sin)

x0,y0,x,y=[],[],[],[]

x0=np.linspace(0,2*np.pi,101)
for item in x0: 
    y0.append(np.sin(item))

for item in x0: 
    x.append([item])
for item in y0: 
    y.append([item])



## Relu functions

def relu(x):
    for i in range(len(x)):
        if x[i] <= 0:
            x[i] = 0
    
    return x
            

def relu_derivative(x):
    for i in range(len(x)):
        if x[i] <= 0:
            x[i] = 0
        else:
            x[i] = 1
    
    return x






# Numpy print option
np.set_printoptions(precision=3)
np.set_printoptions(suppress=True)





# Majority function inputs and outputs
# input dataset
X = np.array ([[0,0,0],
[0,0,1],
[0,1,0],
[0,1,1],
[1,0,0],
[1,0,1],
[1,1,0],
[1,1,1]])

# output dataset
y = np.array([[0,0,0,1,0,1,1,1]]).T