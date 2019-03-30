"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
w, x, y, z = [0]*4
def main():
    __default_nonlocal___ = None
     # new scope 1
    w = goodbye(1, 2, 3, 4, 5, 6, 7, 8)
    print( w )
     # __return__ 2
    return w
    return __BLOCK_DO_NOTHING___, None # default return


def tralala(wang):
    __default_nonlocal___ = None
    x, y, z, w = [0]*4
     # new scope 1
    x = 3
    y = 5
    z = 2
    w = 4
    wang = 42
    print( wang, (x * y), (z * w) )
     # __return__ 2
    return 1
    return __BLOCK_DO_NOTHING___, None # default return


def goodbye(a, b, c, d, e, f, g, h):
    __default_nonlocal___ = None
     # new scope 1
    print( a, b, c, d, e, f, g, h )
    print( "Morna")
     # __return__ 2
    return tralala(1)
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main()
