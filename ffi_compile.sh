#!/bin/sh
# 1. Compiles the vsl file ffi.vsl with functions exported.
# 2. Create the header file ffi.h with the function prototypes
#    of the exported functions in ffi.vsl.
# 3. Compiles the c file ffi.c which will use functions from ffi.vsl
# 4. Compiles ffi.s and links it together with ffi.o.
# --> ffi_vsl is the finished binary.
./compiler --export --no-main < ffi.vsl > ffi.s
./compiler --header < ffi.vsl > ffi.h

./compiler --export --no-main < inline_asm.vsl > inline_asm.s
./compiler --header < inline_asm.vsl > inline_asm.h

gcc -c ffi.c
gcc -o ffi_vsl ffi.s inline_asm.s ffi.o -fPIC -fPIE
