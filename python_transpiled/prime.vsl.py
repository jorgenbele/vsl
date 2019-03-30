"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
"""
VSL version of prime assembly exercise, courtesy
of J.H.Ø. Anthony (class of 2011)
"""
def main():
    __default_nonlocal___ = None
     # new scope 1
     # __return__ 2
    return factor(1836311903)
    return __BLOCK_DO_NOTHING___, None # default return


def factor(n):
    __default_nonlocal___ = None
    f = [0]*1
     # new scope 1
    f = (n // 2)
    while ( (n - (f * (n // f))) > 0 ):
        f = (f - 1)
    if (f - 1) > 0 :
        def block_2():
            nonlocal __default_nonlocal___, n
            nonlocal __default_nonlocal___, f
            r = [0]*1
             # new scope 2
            r = factor(f)
            r = factor((n // f))
            return __BLOCK_DO_NOTHING___, None # default return
        __ret_type___, __ret_val___ = block_2()
        if __ret_type___ == __BLOCK_RETURN___:
            return __ret_val___ # return function
        elif __ret_type___ == __BLOCK_CONTINUE___:
            return __BLOCK_CONTINUE___, None # continue
        
        
    else:
        print( n, "is a prime factor")
     # __return__ 2
    return 0
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main()
