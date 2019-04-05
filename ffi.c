/*
 * Tests linking and running functions from compiled vsl programs.
 *
 * Test using: ffi_compile.sh && ./ffi_vsl
 * See: ffi_compile.sh for how this works.
 */

#include <stdio.h>
#include <inttypes.h>

#include "ffi.h"
#include "inline_asm.h"

int main(int argc, char *argv[])
{
    /* ffi.vsl */
    int64_t i = 0;
    printf("This is printed from c: %lu\n", i);
    i = _print_from_vsl(i);
    printf("From c after _print_from_vsl: returned: %lu\n", i);

    i = _factor(1000);
    i = _euclid(22, 21);

    /* inline_asm.vsl */
    _helloworld();

    const char *s = "This is a write call going through vsl!\n";
    _write(1, (int64_t) s, _strlen(s));

    return 0;
}
