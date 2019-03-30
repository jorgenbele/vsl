"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main(n):
    __default_nonlocal___ = None
    f = [0]*1
     # new scope 1
    f = fibonacci_number(n)
    print( "Fibonacci number #", n, "is", f )
     # __return__ 2
    return 0
    return __BLOCK_DO_NOTHING___, None # default return


def fibonacci_number(n):
    __default_nonlocal___ = None
    y = [0]*1
     # new scope 1
    y = 0
    if n > 2 : y = (fibonacci_number((n - 1)) + fibonacci_number((n - 2)))
    else:
        y = 1
     # __return__ 2
    return y
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main(int(argv[1]))
