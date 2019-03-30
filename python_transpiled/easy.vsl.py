"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main(a):
    __default_nonlocal___ = None
    x, y, z = [0]*3
     # new scope 1
    print( "Testing plain call/return and expression evaluation")
    x = 15
    z = 5
    y = test(x, z)
    print( "The function returned y:=", y )
     # __return__ 2
    return 0
    return __BLOCK_DO_NOTHING___, None # default return


def test(a, b):
    __default_nonlocal___ = None
    c = [0]*1
     # new scope 1
    print( "My parameters are a:=", a, "and b:=", b )
    c = (a + b)
    print( "Their sum is c:=", c )
    c = (a - b)
    print( "Their difference is c:=", c )
    c = (a * b)
    print( "Their product is c:=", c )
    c = (a // b)
    print( "Their ratio is c:=", c )
    print( "(-c):=", -c )
    print( "The sum of their squares is ", ((a * a) + (b * b)) )
     # __return__ 2
    return (a - b)
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main(int(argv[1]))
