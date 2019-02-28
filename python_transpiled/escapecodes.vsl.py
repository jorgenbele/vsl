"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
def main():
    __default_nonlocal___ = None
    a, b = [0]*2
    print( "Testing if printf format codes are left alone.", "\nOutput *should* contain percent characters, but no integers.")
    a = 64
    b = 42
    print( "\tHello, world! %d %d")
    print( "Adding a splash of ANSI color codes - This will only work in a color terminal")
    print( "\t\033[31mRed")
    print( "\t\033[32mGreen")
    print( "\t\033[34mBlue", "\033[0m")
    return 0
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main()
