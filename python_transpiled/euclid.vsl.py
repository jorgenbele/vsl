"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main(a, b):
    __default_nonlocal___ = None
     # new scope 1
    if a < 0 : a = -a
    if b < 0 : b = -b
    if gcd(a, b) > 1 :
        print( "Greatest common divisor of", a, "and", b, "is", gcd(a, b) )
    else:
        print( a, "and", b, "are relative primes")
     # __return__ 2
    return 0
    return __BLOCK_DO_NOTHING___, None # default return


def gcd(a, b):
    __default_nonlocal___ = None
    g = [0]*1
     # new scope 1
    if b > 0 : g = gcd(b, (a - ((a // b) * b)))
    else:
        g = a
     # __return__ 2
    return g
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main(int(argv[1]), int(argv[2]))
