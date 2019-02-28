"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main(n):
    __default_nonlocal___ = None
    w, x, y, f = [0]*4
    w = n
    x = 1
    y = 1
    f = 1
    if w > 0 :
        def block_2():
            nonlocal __default_nonlocal___, n
            nonlocal __default_nonlocal___, w, x, y, f
            if w > 1 :
                if w > 2 :
                    while (w > 3 ):
                        def block_6():
                            nonlocal __default_nonlocal___, n
                            nonlocal __default_nonlocal___, w, x, y, f
                            f = y + x
                            x = y
                            y = f
                            w = w - 1
                            return __BLOCK_DO_NOTHING___, None
                        __ret_type___, __ret_val___ = block_6()
                        if __ret_type___ == __BLOCK_RETURN___:
                            return __ret_type___, __ret_val___  # return to outer block
                        elif __ret_type___ == __BLOCK_CONTINUE___:
                            continue
                        
                        
            return __BLOCK_DO_NOTHING___, None
        __ret_type___, __ret_val___ = block_2()
        if __ret_type___ == __BLOCK_RETURN___:
            return __ret_type___, __ret_val___  # return to outer block
        elif __ret_type___ == __BLOCK_CONTINUE___:
            return __BLOCK_CONTINUE___, None # continue
        
        
    else:
        f = 0
    print( "Fibonacci number #", n, "is", f )
    return 0
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main(int(argv[1]))
