
LEX=flex
YACC=bison
YFLAGS+=--defines=y.tab.h -o y.tab.c -r all
CFLAGS+=-std=c11 -g -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Wpedantic # -DYYSTYPE="void *" # -Wno-incompatible-pointer-types -Wno-int-to-pointer-cast # -DDEBUG
CFLAGS+=-Wno-extra-semi -Wno-unneeded-internal-declaration
CFLAGS+=-Wno-unused-command-line-argument
LDLIBS+=-lc
#CC=musl-clang
CC=clang

.PHONEY: compiler print_symtab y.tab.h clean purge rebuild

all: print_symtab compiler
compiler: compiler.o generator.o parser.o scanner.o nodetypes.o node.o utils.o tree.o node_src.o ir.o tlhash.o
print_symtab: print_symtab.o parser.o scanner.o nodetypes.o node.o utils.o tree.o node_src.o ir.o tlhash.o

y.tab.h: parser.c
scanner.c: y.tab.h scanner.l

clean:
	-rm -f parser.c scanner.c *.tab.* *.o

purge: clean
	-rm -f print_symtab

rebuild: clean purge compiler print_symtab y.tab.h
