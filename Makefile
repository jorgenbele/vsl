
LEX=flex
YACC=bison
YFLAGS+=--defines=y.tab.h -o y.tab.c -r all
CFLAGS+=-std=c11 -g -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Wpedantic # -DYYSTYPE="void *" # -Wno-incompatible-pointer-types -Wno-int-to-pointer-cast # -DDEBUG
CFLAGS+=-Wno-extra-semi -Wno-unneeded-internal-declaration
CFLAGS+=-Wno-unused-command-line-argument
LDLIBS+=-lc
#CC=musl-clang
CC=clang

.PHONEY: main clean purge rebuild

main: main.c parser.o scanner.o nodetypes.o node.o utils.o tree.o node_src.o node_python_src.o #node_source.o
y.tab.h: parser.c
scanner.c: y.tab.h scanner.l

clean:
	-rm -f parser.c scanner.c *.tab.* *.o

purge: clean
	-rm -f main

rebuild: clean purge main y.tab.h
