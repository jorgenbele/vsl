"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main(a, b, c, d, e, f, g):
    __default_nonlocal___ = None
    x = [0]*1
    x = 42
    print( a, b, c, d, e, f, g )
    if x == 42 :
        def block_2():
            nonlocal __default_nonlocal___, a, b, c, d, e, f, g
            nonlocal __default_nonlocal___, x
            print( "Equal!")
            x = 43
            return __BLOCK_DO_NOTHING___, None
        __ret_type___, __ret_val___ = block_2()
        if __ret_type___ == __BLOCK_RETURN___:
            return __ret_type___, __ret_val___  # return to outer block
        elif __ret_type___ == __BLOCK_CONTINUE___:
            return __BLOCK_CONTINUE___, None # continue
        
        
    else:
        def block_2():
            nonlocal __default_nonlocal___, a, b, c, d, e, f, g
            nonlocal __default_nonlocal___, x
            x = 44
            return __BLOCK_DO_NOTHING___, None
        __ret_type___, __ret_val___ = block_2()
        if __ret_type___ == __BLOCK_RETURN___:
            return __ret_type___, __ret_val___  # return to outer block
        elif __ret_type___ == __BLOCK_CONTINUE___:
            return __BLOCK_CONTINUE___, None # continue
        
        
    while ( x > 0 ):
        def block_2():
            nonlocal __default_nonlocal___, a, b, c, d, e, f, g
            nonlocal __default_nonlocal___, x
            print( x )
            x = x - 1
            return __BLOCK_DO_NOTHING___, None
        __ret_type___, __ret_val___ = block_2()
        if __ret_type___ == __BLOCK_RETURN___:
            return __ret_type___, __ret_val___  # return to outer block
        elif __ret_type___ == __BLOCK_CONTINUE___:
            continue
        
        
    return x
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main(int(argv[1]), int(argv[2]), int(argv[3]), int(argv[4]), int(argv[5]), int(argv[6]), int(argv[7]))
