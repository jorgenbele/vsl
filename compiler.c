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
    yyparse();

    tree_simplify(ast_g_root);

    ir_ctx_t ctx;
    ir_ctx_init(&ctx);

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--export"))       ctx.export_functions = 1;
        else if (!strcmp(argv[i], "--header"))  ctx.generate_header = 1;
        else if (!strcmp(argv[i], "--no-main")) ctx.generate_main = 0;
    }

    ir_create_symtab(&ctx, ast_g_root);

    //ir_print_symtab(&ctx, ast_g_root);
    gen_program(&ctx);

    ir_destroy_symtab(&ctx);
    ir_ctx_destroy(&ctx);

    tree_destroy(ast_g_root);
    yylex_destroy();
}
