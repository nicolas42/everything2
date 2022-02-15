# from https://github.com/enkimute/ganja.js/blob/master/codegen/python/r3.py

def mul(a,b):
    # c.e0     =   +a.e0*b.e0  +a.e1*b.e1  +a.e2*b.e2  +a.e3*b.e3  -a.e12*b.e12 -a.e23*b.e23 -a.e31*b.e31 -a.e123*b.e123;
    # c.e1     =   +a.e0*b.e1  +a.e1*b.e0  -a.e2*b.e12  +a.e3*b.e31  +a.e12*b.e2 -a.e23*b.e123 -a.e31*b.e3 -a.e123*b.e23;
    # c.e2     =   +a.e0*b.e2  +a.e1*b.e12  +a.e2*b.e0  -a.e3*b.e23  -a.e12*b.e1 +a.e23*b.e3 -a.e31*b.e123 -a.e123*b.e31;
    # c.e3     =   +a.e0*b.e3  -a.e1*b.e31  +a.e2*b.e23  +a.e3*b.e0  -a.e12*b.e123 -a.e23*b.e2 +a.e31*b.e1 -a.e123*b.e12;
    # c.e12    =   +a.e0*b.e12  +a.e1*b.e2  -a.e2*b.e1  +a.e3*b.e123  +a.e12*b.e0 -a.e23*b.e31 +a.e31*b.e23 +a.e123*b.e3;
    # c.e23    =   +a.e0*b.e23  +a.e1*b.e123  +a.e2*b.e3  -a.e3*b.e2  +a.e12*b.e31 +a.e23*b.e0 -a.e31*b.e12 +a.e123*b.e1;
    # c.e31    =   +a.e0*b.e31  -a.e1*b.e3  +a.e2*b.e123  +a.e3*b.e1  -a.e12*b.e23 +a.e23*b.e12 +a.e31*b.e0 +a.e123*b.e2;
    # c.e123   =   +a.e0*b.e123  +a.e1*b.e23  +a.e2*b.e31  +a.e3*b.e12  +a.e12*b.e3 +a.e23*b.e1 +a.e31*b.e2 +a.e123*b.e0;    

    # [ e0 e1 e2 e3 e12 e23 e31 e123 ] [ e0 e1 e2 e3 e12 e23 e31 e123 ]

    res = [0, 0,0,0, 0,0,0, 0]
    res[0]=b[0]*a[0]+b[1]*a[1]+b[2]*a[2]+b[3]*a[3]-b[4]*a[4]-b[5]*a[5]-b[6]*a[6]-b[7]*a[7]
    res[1]=b[1]*a[0]+b[0]*a[1]-b[4]*a[2]-b[5]*a[3]+b[2]*a[4]+b[3]*a[5]-b[7]*a[6]-b[6]*a[7]
    res[2]=b[2]*a[0]+b[4]*a[1]+b[0]*a[2]-b[6]*a[3]-b[1]*a[4]+b[7]*a[5]+b[3]*a[6]+b[5]*a[7]
    res[3]=b[3]*a[0]+b[5]*a[1]+b[6]*a[2]+b[0]*a[3]-b[7]*a[4]-b[1]*a[5]-b[2]*a[6]-b[4]*a[7]
    res[4]=b[4]*a[0]+b[2]*a[1]-b[1]*a[2]+b[7]*a[3]+b[0]*a[4]-b[6]*a[5]+b[5]*a[6]+b[3]*a[7]
    res[5]=b[5]*a[0]+b[3]*a[1]-b[7]*a[2]-b[1]*a[3]+b[6]*a[4]+b[0]*a[5]-b[4]*a[6]-b[2]*a[7]
    res[6]=b[6]*a[0]+b[7]*a[1]+b[3]*a[2]-b[2]*a[3]-b[5]*a[4]+b[4]*a[5]+b[0]*a[6]+b[1]*a[7]
    res[7]=b[7]*a[0]+b[6]*a[1]-b[5]*a[2]+b[4]*a[3]+b[3]*a[4]-b[2]*a[5]+b[1]*a[6]+b[0]*a[7]
    return res

def init():
    return [0,0,0,0,0,0,0,0]


def scalar(a):
    return [a,0,0,0,0,0,0,0]


def vector(a,b,c):
    return [0,a,b,c,0,0,0,0]


def bivector(a,b,c):
    return [0,0,0,0,a,b,c,0]


def trivector(a):
    return [0,0,0,0,0,0,0,a]

def print_multivector(c):

    print("(" , end="")
    if ( c[0] != 0 ): print(" %+.2f" % c[0] , end="")
    if ( c[1] != 0 ): print(" %+.2fx" % c[1] , end="")
    if ( c[2] != 0 ): print(" %+.2fy" % c[2] , end="")
    if ( c[3] != 0 ): print(" %+.2fz" % c[3] , end="")
    if ( c[4] != 0 ): print(" %+.2fxy" % c[4] , end="")
    if ( c[5] != 0 ): print(" %+.2fyz" % c[5] , end="")
    if ( c[6] != 0 ): print(" %+.2fzx" % c[6] , end="")
    if ( c[7] != 0 ): print(" %+.2fxyz" % c[7] , end="")
    print(" )" , end="\n")


if __name__ == "__main__":
    from math import *



    # hammer h, saw s, toolbox t 

    # h+s+0=10
    # 0+s+t=20
    # h+0+t=24

    # (h+s) -(s+t) + (h+t) = 10-20+24
    # h = 7
    # s = 3
    # t = 17

    # but that's too simple.  
    # instead we define an abstract vector space and use clifford algebra 

    # define vectors a,b,c

    # ah + bs + ct = d 
    # (x+z)h + (x+y)s + (y+z)t = (10x+20y+24z)

    # cramer's rule 
    # h = d^b^c / a^b^c 
    # s = d^a^c / a^b^c 
    # t = a^b^d / a^b^c 

    # a^b^c = (x+z)(x+y)(y+z) = (1+xy+zx+zy)(y+z) = (y+z+x+xzy +zxy +zxz + z + zyz ) 
    # =  x+y+2z+

    a = vector(1,0,1)
    b = vector(1,1,0)
    c = vector(0,1,1)
    d = vector(10,20,24)

    
    abc = mul(mul(a,b),c)
    dbc = mul(mul(d,b),c)
    adc = mul(mul(a,d),c)
    abd = mul(mul(a,b),d)

    for mv in [abc,dbc,adc,abd]: print_multivector(mv)

    print("h,s,t: ", dbc[7]/abc[7], adc[7]/abc[7], abd[7]/abc[7] )



    # a = vector(1,1,0)
    # b = vector(0,1,0)
    # c = vector(0,0,1)
    # print(mul(a,mul(b,c)))





    # tau = 2*pi

    # v = vector(cos(tau/8), sin(tau/8), 0)
    # a = vector(cos(tau/8), sin(tau/8), 0)

    # # spherical coordinates to cartesian
    # # x = r cos(phi) sin(theta)
    # # y = r sin(phi) sin(theta)
    # # z = r cos(theta)

    # b = vector(cos(tau/8)*sin(tau/8), sin(tau/8)*sin(tau/8), cos(tau/8))

    # # rotate v by twice the angle between a and b

    # bavab = mul(mul(mul(mul(b,a),v),a),b)
    # print_multivector(bavab)


