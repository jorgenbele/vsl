"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
"""
This program tests activation records, function call and return
"""
def main():
    __default_nonlocal___ = None
    x, y, z = [0]*3
     # new scope 1
    x = 5
    y = 10
    print( "Calling my_function with parameters", x, y )
    z = my_function(x, y)
    print( "The returned result is", z )
    z = my_other_function()
    print( "The other returned result is", z )
     # __return__ 2
    return 0
    return __BLOCK_DO_NOTHING___, None # default return


def my_function(s, t):
    __default_nonlocal___ = None
    u = [0]*1
     # new scope 1
    u = (s * s) + (t * t)
    print( "Parameter s is", s )
    print( "Parameter t is", t )
    print( "The sum of their squares is", u )
     # __return__ 2
    return u
    return __BLOCK_DO_NOTHING___, None # default return


def my_other_function():
    __default_nonlocal___ = None
    x = [0]*1
     # new scope 1
    x = 42
     # __return__ 2
    return x
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main()
