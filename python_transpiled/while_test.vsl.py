"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main():
    __default_nonlocal___ = None
    a = [0]*1
    a = 20
    print( a )
    if a > 0 :
        print( "foobar")
    while ( a > 0 ):
        def block_2():
            nonlocal __default_nonlocal___, a
            if a == 10 :
                def block_4():
                    nonlocal __default_nonlocal___, a
                    a = a - 1
                    print( "Skip...")
                    return __BLOCK_CONTINUE___, None
                    return __BLOCK_DO_NOTHING___, None
                __ret_type___, __ret_val___ = block_4()
                if __ret_type___ == __BLOCK_RETURN___:
                    return __ret_type___, __ret_val___  # return to outer block
                elif __ret_type___ == __BLOCK_CONTINUE___:
                    return __BLOCK_CONTINUE___, None # continue
                
                
            else:
                a = a - 1
            print( a )
            return __BLOCK_DO_NOTHING___, None
        __ret_type___, __ret_val___ = block_2()
        if __ret_type___ == __BLOCK_RETURN___:
            return __ret_type___, __ret_val___  # return to outer block
        elif __ret_type___ == __BLOCK_CONTINUE___:
            continue
        
        
    return 0
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main()
