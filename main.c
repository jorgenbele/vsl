#include <stdio.h>
#include <stdlib.h>

#include "vslc.h"

node_t *root;

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;
    yyparse();

    debug("==== NON-SIMPLIFIED ====");
    node_print(root, 0);

    //tree_simplify(root, NULL);
    tree_simplify(root);

    debug("\n\n==== SIMPLIFIED ====");
    node_print(root, 0);

    tree_destroy(root);
    yylex_destroy();
}
