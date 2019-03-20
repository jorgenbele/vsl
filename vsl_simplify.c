/*
 * Parses and simplifies and prints the simplified tree.
 */
#include <stdio.h>
#include <stdlib.h>

#include "vslc.h"
/*  #include "node_source.h" */
#include "node_python_src.h"
#include "node_src.h"

node_t *ast_g_root;

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  yyparse();

  tree_simplify(ast_g_root);

  node_print(ast_g_root, 0);

  tree_destroy(ast_g_root);
  yylex_destroy();
}
