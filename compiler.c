#include <stdio.h>
#include <stdlib.h>

#include "vslc.h"
/*  #include "node_source.h" */

#include "tlhash.h"
#include "ir.h"
#include "generator.h"

 /* Externally used global. */
node_t *ast_g_root;

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;
    yyparse();

    tree_simplify(ast_g_root);

    ir_ctx_t ctx;
    ir_ctx_init(&ctx);

    ir_create_symtab(&ctx, ast_g_root);

    //ir_print_symtab(&ctx, ast_g_root);
    gen_program(&ctx);

    ir_destroy_symtab(&ctx);
    ir_ctx_destroy(&ctx);

    tree_destroy(ast_g_root);
    yylex_destroy();
}
