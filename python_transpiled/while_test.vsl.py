"""
Transpiled from vsl to python 3
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main():
    __default_nonlocal___ = None
    a = [0]*1
     # new scope 1
    a = 20
    print( a )
    if a > 0 :
        print( "foobar")
    while ( a > 0 ):
        def block_3():
            nonlocal __default_nonlocal___, a
             # new scope 3
            if a == 10 :
                def block_4():
                    nonlocal __default_nonlocal___, a
                     # new scope 4
                    a = (a - 1)
                    print( "Skip...")
                    return __BLOCK_CONTINUE___, None
                    return __BLOCK_DO_NOTHING___, None # default return
                __ret_type___, __ret_val___ = block_4()
                if __ret_type___ == __BLOCK_RETURN___:
                    return __ret_type___, __ret_val___  # return to outer block
                elif __ret_type___ == __BLOCK_CONTINUE___:
                    return __BLOCK_CONTINUE___, None # continue
                
                
            else:
                a = (a - 1)
            print( a )
            return __BLOCK_DO_NOTHING___, None # default return
        __ret_type___, __ret_val___ = block_3()
        if __ret_type___ == __BLOCK_RETURN___:
            return __ret_val___ # return function
        elif __ret_type___ == __BLOCK_CONTINUE___:
            continue
        
        
     # __return__ 2
    return 0
    return __BLOCK_DO_NOTHING___, None # default return


if __name__ == '__main__':
    main()
