#include <stdio.h>
#include <stdlib.h>

#include "vslc.h"

node_t *root;

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;
    yyparse();
    node_print(root, 0);
    tree_destroy(root);
}
