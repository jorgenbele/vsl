/*
 * Parses, simplifies and recreates a vsl source file.
 */
#include <stdio.h>
#include <stdlib.h>

#include "node_src.h"
#include "vslc.h"

node_t *root;

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  yyparse();

  tree_simplify(root);
  node_print_source(root);

  tree_destroy(root);
  yylex_destroy();
}
