
LEX=flex
YACC=bison
YFLAGS+=--defines=y.tab.h -o y.tab.c
CFLAGS+=-std=c99 -g -Isrc -Iinclude -D_POSIX_C_SOURCE=200809L -DYYSTYPE="node_t *"
LDLIBS+=-lc

main: main.c parser.o scanner.o nodetypes.o node.o utils.o tree.o
y.tab.h: parser.c
scanner.c: y.tab.h scanner.l
clean:
	-rm -f parser.c scanner.c *.tab.* *.o
purge: clean
	-rm -f vslc