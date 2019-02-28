"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main(a):
    __default_nonlocal___ = None
    print( a )
    if a > 10 :
        print( "Bigger")
    if a < 10 :
        print( "Smaller")
    if a == 10 :
        print( "Equal")
    return 0
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main(int(argv[1]))
