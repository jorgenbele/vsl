"""
Transpiled from vsl to python
"""
from sys import argv

def main(a):
    __default_nonlocal___ = None
    print( "Testing plain call/return and expression evaluation")
    x = 15
    z = 5
    y = test(x, z)
    print( "The function returned y:=", y )
    return 0


def test(a, b):
    __default_nonlocal___ = None
    print( "My parameters are a:=", a, "and b:=", b )
    c = a + b
    print( "Their sum is c:=", c )
    c = a - b
    print( "Their difference is c:=", c )
    c = a * b
    print( "Their product is c:=", c )
    c = a // b
    print( "Their ratio is c:=", c )
    print( "(-c):=", -c )
    print( "The sum of their squares is ", (a * a) + (b * b) )
    return a - b


if __name__ == '__main__':
	main(int(argv[1]))
