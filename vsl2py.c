/*
 * Transpiles from vsl to python 3.
 */

#include <stdio.h>
#include <stdlib.h>

#include "node_python_src.h"
#include "vslc.h"

node_t *root;

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  yyparse();

  tree_simplify(root);

  transpile_to_python(root);

  tree_destroy(root);
  yylex_destroy();
}
