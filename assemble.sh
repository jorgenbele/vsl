#!/bin/sh
# input file  - $1
# output file - $2
gcc -g -o "$2" "$1" -fPIC -fPIE
