import random
# import numpy

def get_digit(number, n):
    return number // 10**n % 10

def cumulative_sum(a):
    i = 1
    while i < len(a):
        a[i] += a[i-1]
        i+=1
    return a 


# a = [ 111, 905, 806, 307, 518, 721, 462, 163, 263, 166, 277, 779, 681, 284, 787, 988, 395, 280, 370, 4095]

a = []
for i in range(1,10):
    for j in range(10**6):
        a.append(random.randint(0,10**i))

random.shuffle(a)

for digit in range(0,10):
    o = [[],[],[],[],[],[],[],[],[],[]]
    for i in a:
        number = get_digit(i,digit)
        o[number].append(i)

    a = []
    for i in o:
        for j in i:
            a.append(j)

    print(a)