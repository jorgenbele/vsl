"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main():
    __default_nonlocal___ = None
    x = [0]*1
    print( "Nested scopes coming up...")
    x = test_me(1)
    print( "x:=", x )
    return 0
    return __BLOCK_DO_NOTHING___, None


def test_me(a):
    __default_nonlocal___ = None
    print( "Parameter a is a:=", a )
    def block_1():
        nonlocal __default_nonlocal___
        a = [0]*1
        a = 2
        print( "Outer scope has a:=", a )
        def block_2():
            nonlocal __default_nonlocal___
            nonlocal __default_nonlocal___
            b, a = [0]*2
            a = 3
            b = 4
            def block_3():
                nonlocal __default_nonlocal___, a
                nonlocal __default_nonlocal___, a
                nonlocal __default_nonlocal___, b, a
                print( "Inner scope has a:=", a, "and b:=", b )
                b = 5
                return __BLOCK_DO_NOTHING___, None
            __ret_type___, __ret_val___ = block_3()
            if __ret_type___ == __BLOCK_RETURN___:
                return __ret_type___, __ret_val___  # return to outer block
            elif __ret_type___ == __BLOCK_CONTINUE___:
                return __BLOCK_CONTINUE___, None # continue
            
            
            print( "b was updated to ", b, "in inner scope")
            return __BLOCK_DO_NOTHING___, None
        __ret_type___, __ret_val___ = block_2()
        if __ret_type___ == __BLOCK_RETURN___:
            return __ret_type___, __ret_val___  # return to outer block
        elif __ret_type___ == __BLOCK_CONTINUE___:
            return __BLOCK_CONTINUE___, None # continue
        
        
        print( "Outer scope (still) has a:=", a )
        return __BLOCK_DO_NOTHING___, None
    __ret_type___, __ret_val___ = block_1()
    if __ret_type___ == __BLOCK_RETURN___:
        return __ret_val___ # return function
    elif __ret_type___ == __BLOCK_CONTINUE___:
        return __BLOCK_CONTINUE___, None # continue
    
    
    print( "Return expression (a-1) using a:=", a )
    return a - 1
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main()
