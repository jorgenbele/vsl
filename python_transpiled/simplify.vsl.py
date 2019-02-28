"""
Transpiled from vsl to python
"""
from sys import argv

__BLOCK_DO_NOTHING___ = 0
__BLOCK_CONTINUE___ = 1
__BLOCK_RETURN___ = 2
"""
Function list
"""
def f():
    __default_nonlocal___ = None
    return 0
    return __BLOCK_DO_NOTHING___, None


def g(a, b, c):
    __default_nonlocal___ = None
    u, v, w, x, y, z = [0]*6
    u = 1
    v = 2
    w = g((x + 1), (y + 2), (z + 3))
    print( u, v, w )
    return 0
    return __BLOCK_DO_NOTHING___, None


def h(a, b):
    __default_nonlocal___ = None
    x = [0]*1
    x = 2 + 3
    x = 3 - 2
    x = 2 * 2
    x = 4 // 2
    x = -6
    x = ((2 + 3) * 4) // 5
    return 0
    return __BLOCK_DO_NOTHING___, None


def main():
    __default_nonlocal___ = None
    x = [0]*1
    x = f()
    x = g(1, 2, 4)
    x = h(2, 5)
    return 0
    return __BLOCK_DO_NOTHING___, None


if __name__ == '__main__':
	main()
