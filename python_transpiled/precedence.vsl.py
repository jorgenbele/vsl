"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
"""
Test parentheses/precedence w. 2*(3-1) vs 2*3-1
"""
def main():
    __default_nonlocal___ = None
    a, b, c, d = [0]*4
    a = 2
    b = 3
    c = 1
    d = a * (b - c)
    print( "2*(3-1) := ", d )
    d = (a * b) - c
    print( "2*3-1 := ", d )
    return 0
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main()
