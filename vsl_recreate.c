/*
 * Parses, simplifies and recreates a vsl source file.
 */
#include <stdio.h>
#include <stdlib.h>

#include "node_src.h"
#include "vslc.h"

node_t *ast_g_root;

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  yyparse();

  tree_simplify(ast_g_root);
  node_print_source(ast_g_root);

  tree_destroy(ast_g_root);
  yylex_destroy();
}
