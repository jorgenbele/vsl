
LEX=flex
YACC=bison
YFLAGS+=--defines=y.tab.h -o y.tab.c -r all
CFLAGS+=-std=c11 -g -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Wpedantic -O3
LDLIBS+=-lc
CC=clang
#CC=gcc

.PHONEY: main vsl_simplify vsl2py vsl_recreate clean purge rebuild

all: main vsl_simplify vsl2py vsl_recreate print_symtab compiler

compiler: compiler.c parser.o scanner.o nodetypes.o node.o utils.o tree.o tlhash.o ir.o node_src.o generator.o

#vsl_simplify: vsl_simplify.c parser.o scanner.o nodetypes.o node.o utils.o tree.o node_python_src.o

vsl_simplify: vsl_simplify.c parser.c scanner.c nodetypes.c node.c utils.c tree.c node_python_src.c
    # Requires recompilation as it uses different compile-time flags.
	clang -o vsl_simplify vsl_simplify.c parser.c scanner.c nodetypes.c node.c utils.c tree.c node_python_src.c -DUSE_TREE_CORRECT_RULES

vsl_simplify_noncorrect: vsl_simplify.c parser.c scanner.c nodetypes.c node.c utils.c tree.c node_python_src.c
    # Requires recompilation as it uses different compile-time flags.
	clang -o vsl_simplify_noncorrect vsl_simplify.c parser.c scanner.c nodetypes.c node.c utils.c tree.c node_python_src.c

vsl2py: vsl2py.c parser.o scanner.o nodetypes.o node.o utils.o tree.o node_python_src.o

main: main.c parser.o scanner.o nodetypes.o node.o utils.o tree.o node_src.o node_python_src.o #node_source.o

vsl_recreate: vsl_recreate.c parser.o scanner.o nodetypes.o node.o utils.o tree.o node_src.o

# uses ir.c and tlhash.c
#print_symtab: print_symtab.c parser.o scanner.o nodetypes.o node.o utils.o tree.o node_src.o ir.c tlhash.c # with ir

print_symtab: print_symtab.c parser.o scanner.o nodetypes.o node.o utils.o tree.o node_src.o ir.o tlhash.o

# Requires recompilation as it uses different compile-time flags.
#	clang -g -o print_symtab print_symtab.c parser.c scanner.c nodetypes.c node.c utils.c tree.c node_python_src.c ir.c tlhash.c

y.tab.h: parser.c
scanner.c: y.tab.h scanner.l

clean:
	-rm -f parser.c scanner.c *.tab.* *.o

purge: clean
	-rm -f compiler main vsl_simplify vsl2py vsl_recreate print_symtab

rebuild: clean purge all main vsl_simplify vsl2py vsl_recreate print_symtab y.tab.h
