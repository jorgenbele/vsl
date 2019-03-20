#include <stdio.h>
#include <stdlib.h>

#include "vslc.h"
/*  #include "node_source.h" */
#include "node_src.h"
#include "node_python_src.h"

#include "tlhash.h"
#include "ir.h"

 /* Externally used global. */
node_t *ast_g_root;

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;
    yyparse();

    //debug("==== NON-SIMPLIFIED ====\n");
    //node_print(root, 0);

    ////tree_simplify(root, NULL);
    tree_simplify(ast_g_root);

    debug("\n\n==== SIMPLIFIED ====\n");
    node_print(ast_g_root, 0);

    debug("\n\n==== SOURCE ====\n\n");
    src_print_fileno = 2;
    node_print_source(ast_g_root);

    //debug("\n\n==== PYTHON SOURCE ====\n\n");
    //python_src_print_fileno = 2;
    transpile_to_python(ast_g_root);

    tree_destroy(ast_g_root);
    yylex_destroy();
}
