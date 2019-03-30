"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main(n):
    __default_nonlocal___ = None
    w, x, y, f = [0]*4
     # new scope 1
    w = n
    x = 1
    y = 1
    f = 1
    if w > 0 :
        def block_2():
            nonlocal __default_nonlocal___, n
            nonlocal __default_nonlocal___, w, x, y, f
             # new scope 2
            if w > 1 :
                if w > 2 :
                    while (w > 3 ):
                        def block_4():
                            nonlocal __default_nonlocal___, n
                            nonlocal __default_nonlocal___, w, x, y, f
                             # new scope 4
                            f = (y + x)
                            x = y
                            y = f
                            w = (w - 1)
                            return __BLOCK_DO_NOTHING___, None # default return
                        __ret_type___, __ret_val___ = block_4()
                        if __ret_type___ == __BLOCK_RETURN___:
                            return __ret_type___, __ret_val___  # return to outer block
                        elif __ret_type___ == __BLOCK_CONTINUE___:
                            continue
                        
                        
            return __BLOCK_DO_NOTHING___, None # default return
        __ret_type___, __ret_val___ = block_2()
        if __ret_type___ == __BLOCK_RETURN___:
            return __ret_val___ # return function
        elif __ret_type___ == __BLOCK_CONTINUE___:
            return __BLOCK_CONTINUE___, None # continue
        
        
    else:
        f = 0
    print( "Fibonacci number #", n, "is", f )
     # __return__ 2
    return 0
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main(int(argv[1]))
