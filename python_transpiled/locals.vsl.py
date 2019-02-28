"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
i, j, k = [0]*3
"""
This program tests the evaluation of local scopes
"""
def main(x, y, z):
    __default_nonlocal___ = None
    a, b, c, d = [0]*4
    a = 21
    def block_1():
        nonlocal __default_nonlocal___, x, y, z
        nonlocal __default_nonlocal___, c, d
        e, f, a, b = [0]*4
        a = 42
        print( "Inner a is ", a )
        return __BLOCK_DO_NOTHING___, None
    __ret_type___, __ret_val___ = block_1()
    if __ret_type___ == __BLOCK_RETURN___:
        return __ret_val___ # return function
    elif __ret_type___ == __BLOCK_CONTINUE___:
        return __BLOCK_CONTINUE___, None # continue
    
    
    print( "Outer a is ", a )
    print( "Global k is ", k )
    return 0
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main(int(argv[1]), int(argv[2]), int(argv[3]))
