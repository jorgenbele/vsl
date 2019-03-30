"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
"""
This program tests the evaluation of the unary minus
"""
def main():
    __default_nonlocal___ = None
    a, b = [0]*2
     # new scope 1
    a = 100
    b = 20
    print( "a is", a, "and b is", b )
    print( "a/(-b) is", (a // (-b)) )
    print( "10/(-2) is", (10 // (-2)) )
     # __return__ 2
    return 0
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main()
