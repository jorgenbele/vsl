"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main():
    __default_nonlocal___ = None
    t = [0]*1
    t = test(42)
    return 0
    return __BLOCK_DO_NOTHING___, None


def test(a):
    __default_nonlocal___ = None
    x, y = [0]*2
    x = 32
    y = 20
    print( "Outer x is", x, "y is", y, "parm is", a )
    def block_1():
        nonlocal __default_nonlocal___, a
        nonlocal __default_nonlocal___, y
        x = [0]*1
        x = 64
        print( "Inner x is", x, "y is", y, "parm is", a )
        return __BLOCK_DO_NOTHING___, None
    __ret_type___, __ret_val___ = block_1()
    if __ret_type___ == __BLOCK_RETURN___:
        return __ret_val___ # return function
    elif __ret_type___ == __BLOCK_CONTINUE___:
        return __BLOCK_CONTINUE___, None # continue
    
    
    print( "Outer x is", x, "y is", y, "parm is", a )
    return 0
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main()
