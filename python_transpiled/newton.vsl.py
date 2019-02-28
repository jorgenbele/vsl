"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
x, y, z = [0]*3
a, b, c = [0]*3
"""
Approximate square root by the Newton/Raphson method for f(x) := x^2 - n
f(x) := x^2 - n := 0
f'(x) := 2x
x{n+1} := x{n} - (x^2-n) / 2x 
"""
def main(n):
    __default_nonlocal___ = None
    square_root = [0]*1
    square_root = improve(n, 1)
    print( "The square root of", n, "is", square_root )
    return 0
    return __BLOCK_DO_NOTHING___, None


def improve(n, estimate):
    __default_nonlocal___ = None
    next = [0]*1
    next = estimate - (((estimate * estimate) - n) // (2 * estimate))
    if next - estimate == 0 :
        return next - 1
    else:
        return improve(n, next)
    return __BLOCK_DO_NOTHING___, None


def fourty_two(x):
    __default_nonlocal___ = None
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main(int(argv[1]))
