"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
"""
This program is a simple test of conditionals, including nesting
"""
def main():
    __default_nonlocal___ = None
    a, b = [0]*2
     # new scope 1
    a = 10
    b = -15
    print( a )
    if a == 10 :
        print( "A equals 10")
    if a > 0 :
        def block_2():
            nonlocal __default_nonlocal___, a, b
             # new scope 2
            if b > -15 :
                print( "B is greater than -15")
            else:
                print( "B is smaller than or equal to -15")
            return __BLOCK_DO_NOTHING___, None # default return
        __ret_type___, __ret_val___ = block_2()
        if __ret_type___ == __BLOCK_RETURN___:
            return __ret_val___ # return function
        elif __ret_type___ == __BLOCK_CONTINUE___:
            return __BLOCK_CONTINUE___, None # continue
        
        
     # __return__ 2
    return 0
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main()
