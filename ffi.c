/*
 * Test using: ffi_compile.sh && ./ffi_vsl
 */

#include <stdio.h>
#include <inttypes.h>

#include "ffi.h"

int main(int argc, char *argv[])
{
    int64_t i = 0;
    printf("This is printed from c: %lu\n", i);
    i = _print_from_vsl(i);
    printf("From c after _print_from_vsl: returned: %lu\n", i);

    i = _factor(1000);

    i = _euclid(22, 21);

    return 0;
}
