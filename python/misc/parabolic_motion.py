# 2D Parabolic motion 
# --------------------------------
# 
# Want to know what angle and initial velocity is necessary to hit a point x,y
# 
# Initial velocity v, angle angle, and gravitational acceleration g
# 
# x = v cos(angle) t
# y = v sin(angle) t + g t^2 / 2
# 



import math

def find_roots_of_quadratic_equation(a,b,c):
    # ax^2 + bx + c = 0
    roots = []
    if b*b >= 4*a*c: 
        roots.append( -b/2/a + math.sqrt(b*b - 4*a*c)/2/a )
        roots.append( -b/2/a - math.sqrt(b*b - 4*a*c)/2/a )
    return roots


def find_angle_from_distance(x = 30, y = 0, v = 20, g = -9.81):
    
    # find angle given position x, y
    # ( g x^2 / 2 v^2 ) tan^2(angle)  + x * tan(angle)  - ( y + g x^2 / 2 v^2 )  = 0
    # 
    a = g * x**2 / 2 / v**2
    b = x
    c = -y + g * x**2 / 2 / v**2

    roots = find_roots_of_quadratic_equation(a,b,c)
    return [ math.atan(i)*180/math.pi for i in roots ]

def find_distance_from_angle(angle = math.pi/4, v = 20, y = 0, g = -9.81):

    # find distance x from height and angle
    # ( g / 2 v^2 ) ( 1 + tan^2(angle) ) x^2  + tan(angle) x  + y = 0
    # 
    a = g / 2 / v**2 * ( 1 + (math.tan(angle))**2 )
    b = math.tan(angle) 
    c = y

    roots = find_roots_of_quadratic_equation(a,b,c)
    return roots

if __name__ == "__main__":

    import sys
    print("desired x y position and the velocity of the projectile")
    print("x y v")
    print(sys.argv)

    x = float(sys.argv[1])
    x = float(sys.argv[2])
    x = float(sys.argv[3])
    
    a = find_angle_from_distance( x = 30, y = 5, v = 50)
    print("angle(s) that can hit this position: ", a)
    
    b = find_distance_from_angle( angle = math.pi / 6 )
    # print(a,b)

"""
    # maximize distance from angle
    a = g / 2 / v**2 * ( 1 + (math.tan(angle))**2 )
    b = math.tan(angle) 
    c = y
    roots.append( -b/2/a - math.sqrt(b*b - 4*a*c)/2/a )
"""
