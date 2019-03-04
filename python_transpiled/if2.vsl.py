"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main(a):
    __default_nonlocal___ = None
     # new scope 1
    print( a )
    if a > 10 :
        print( "Bigger")
    if a < 10 :
        print( "Smaller")
    if a == 10 :
        print( "Equal")
     # __return__ 2
    return 0
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main(int(argv[1]))
