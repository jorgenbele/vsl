#include <stdio.h>
#include <stdlib.h>

#include "vslc.h"
/*  #include "node_source.h" */
#include "node_src.h"
#include "node_python_src.h"

node_t *root;

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;
    yyparse();

    //debug("==== NON-SIMPLIFIED ====\n");
    //node_print(root, 0);

    ////tree_simplify(root, NULL);
    tree_simplify(root);

    //debug("\n\n==== SIMPLIFIED ====\n");
    //node_print(root, 0);

    //debug("\n\n==== SOURCE ====\n\n");
    //node_print_source(root);
    transpile_to_python(root);

    tree_destroy(root);
    yylex_destroy();
}
