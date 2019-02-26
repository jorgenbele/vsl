/*
 * Parses and simplifies and prints the simplified tree.
 */
#include <stdio.h>
#include <stdlib.h>

#include "vslc.h"
/*  #include "node_source.h" */
#include "node_python_src.h"
#include "node_src.h"

node_t *root;

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  yyparse();

  tree_simplify(root);

  node_print(root, 0);

  tree_destroy(root);
  yylex_destroy();
}
