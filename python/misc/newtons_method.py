
"""
Newton's method
start at an arbitrary x0
calculate the tangent line
find its x-intercept
find the tangent line at that x-intercept
repeat

y-y0 = m(x-x0)
find x-intercept when y=0
-y0 / m + x0 = x

"""


import math

def get_derivative_of(eq):
    # eq = [ 12, 31, 23, 123, 123, 123 ]
    # remove first number
    out = eq.copy()
    for i,v in enumerate(eq):
        # print(i,v)
        out[i] = i * eq[i]
    out = out[ 1: ]
    return out


def evaluate(f, x):
    result = 0.0
    for i,v in enumerate(f):
        result += f[i] * math.pow(x,i)
    return result


def newtons_method(f,x0):
    df_dx = get_derivative_of(f)
    while True:
        y0 = evaluate(f,x0)
        m = evaluate(df_dx, x0)
        x_intercept = -y0 / m + x0
        # print(x_intercept)
        if (abs(x_intercept - x0) < 1e-10):
            break
        x0 = x_intercept
        # print(x0)
    return x_intercept


def find_roots(f,xs):
    roots = set()
    for x in xs:
        r = newtons_method(f,x)
        r = round(r, 7)
        roots.add(r)
    roots = list(roots)
    roots.sort()
    return roots

import numpy as np

if __name__ == "__main__":
    # y = 2 +x -x^2
    f = [ 2,1,-1]
    xs = range(-100,100)
    find_roots(f,xs)

    #  y = 1 + 23x + 12x^2 + 213x^3 ...
    f = [1,23,12,312,31,23,123,-123]
    xs = np.arange(-100,100, 0.1)
    roots = find_roots(f,xs)
    print(roots)
    # check with wolfram alpha 
    # https://www.wolframalpha.com/input/?i=roots+of+1%2B23x%2B12x%5E2%2B312x%5E3%2B31x%5E4%2B23x%5E5%2B123x%5E6-123x%5E7

