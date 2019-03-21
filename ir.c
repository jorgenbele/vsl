#include "ir.h"

#include <assert.h>
#include <stdint.h>

#include "tree.h"
#include "utils.h"

#define IR_TLHASH_BUCKETS 512
#define IR_LOCALS_TLHASH_BUCKETS 128

/* Define vector functions. */
DEF_VEC_FUNCS(ir_str, ir_str, NULL);
DEF_VEC_FUNCS(symbol_t_ptr, symbol_t_ptr, NULL);
DEF_VEC_FUNCS(tlhash_t_ptr, tlhash_t_ptr, NULL);

#define PUSH_SYMBOL(ctx, sym) VEC_PUSH(&(ctx)->symbols, symbol_t_ptr, sym)

/* ir_ctx_init: Initialize an ir context. Must be done before use. */
void ir_ctx_init(ir_ctx_t *ctx)
{
    memset(&ctx->names, 0, sizeof(ctx->names));
    assert(!tlhash_init(&ctx->names, IR_TLHASH_BUCKETS));

    VEC_INIT(&ctx->strings, ir_str);
    VEC_INIT(&ctx->scopes, tlhash_t_ptr);
    VEC_INIT(&ctx->symbols, symbol_t_ptr);

    ctx->temp = NULL;
    ctx->temp_size = 0;

    ctx->seq = 0;
}

#define DESTROY_TLHASH_SYMBS(tlhash_ptr)                        \
    do {                                                        \
        size_t n_globals = tlhash_size(tlhash_ptr);             \
        symbol_t **temp = xcalloc(n_globals, sizeof(*temp));    \
        tlhash_values(tlhash_ptr, (void **) temp);              \
        for (size_t i = 0; i < n_globals; i++) {                \
            ir_symbol_destroy(temp[i]);                         \
        }                                                       \
        free(temp);                                             \
    } while (0)

/* ir_ctx_destroy: Destroy an ir context. */
void ir_ctx_destroy(ir_ctx_t *ctx)
{
    assert(!tlhash_finalize(&ctx->names));

    VEC_DESTROY(&ctx->strings, ir_str);
    VEC_DESTROY(&ctx->scopes, tlhash_t_ptr);

    while (!VEC_ERROR(&ctx->symbols) && VEC_LEN(&ctx->symbols) > 0) {
        symbol_t *symb = VEC_POP(&ctx->symbols, symbol_t_ptr);
        free(symb);
    }
    VEC_DESTROY(&ctx->symbols, symbol_t_ptr);
    if (ctx->temp) free(ctx->temp);
}

static int extend_temp(ir_ctx_t *ctx, size_t new_size)
{
    if (ctx->temp_size < new_size) {
        ctx->temp_size = new_size;
        ctx->temp = xrealloc(ctx->temp, new_size*sizeof(*ctx->temp));
        return 1;
    }
    return 0;
}

/* ir_create_symtab: Create the symbol table from the ast. */
void ir_create_symtab(ir_ctx_t *ctx, node_t *root)
{
    ir_find_globals(ctx, root);

    size_t n_globals = tlhash_size ( &ctx->names );
    extend_temp(ctx, n_globals);
    symbol_t **temp = ctx->temp;
    tlhash_values(&ctx->names, (void **) temp);
    for (size_t i = 0; i < n_globals; i++)
        if (temp[i]->type == SYM_FUNCTION)
            ir_bind_names(ctx, temp[i], temp[i]->node);
}

void ir_symbol_destroy(symbol_t *symb)
{
    if (symb->type == SYM_FUNCTION && symb->locals) {
        //DESTROY_TLHASH_SYMBS(symb->locals);
        //tlhash_finalize(symb->locals);
        VEC_DESTROY(symb->locals, symbol_t_ptr);
        free(symb->locals);
    }
}

void ir_destroy_symtab(ir_ctx_t *ctx)
{
    size_t n_globals = tlhash_size ( &ctx->names );
    extend_temp(ctx, n_globals);
    symbol_t **temp = ctx->temp;
    tlhash_values(&ctx->names, (void **) temp);
    for (size_t i = 0; i < n_globals; i++)
        ir_symbol_destroy(temp[i]);
}

#define IR_INSERT_GLOBAL_SYMBOL(ctx, symb)                              \
    tlhash_insert(&(ctx)->names, (symb)->name, (symb)->name_len, (symb))

//inline static symbol_t *ir_symbol_new(char *name, size_t name_len, symtype_t type, node_t *node,
//                       size_t seq, size_t nparms, tlhash_t *locals)
inline static symbol_t *ir_symbol_new(char *name, size_t name_len, symtype_t type, node_t *node,
                       size_t seq, size_t nparms, VEC(symbol_t_ptr) *locals)
{
    symbol_t *symb = xcalloc(1, sizeof(*symb));
    *symb = (symbol_t){name, name_len, type, node, seq, nparms, locals};
    return symb;
}

inline static void add_function_symbol(ir_ctx_t *ctx, node_t *func_node)
{
    assert(func_node->type == FUNCTION);
    assert(func_node->n_children >= 2);
    assert(func_node->children[0]->type == IDENTIFIER_DATA);

    /* The 2nd (index 1) will ALWAYS be the parameter list.
     * NOTE that this is a modification that I made. */
    assert(func_node->children[1]->type == VARIABLE_LIST);

    node_t *ident = func_node->children[0];
    const node_t *params = func_node->children[1];

    symbol_t *symb = ir_symbol_new(ident->data_char_ptr, strlen(ident->data_char_ptr),
                                   SYM_FUNCTION, func_node, ctx->seq++, params->n_children, NULL);
    PUSH_SYMBOL(ctx, symb);
    IR_INSERT_GLOBAL_SYMBOL(ctx, symb);
}

inline static void add_global_variable_list_symbol(ir_ctx_t *ctx, node_t *node)
{
    assert(node->type == VARIABLE_LIST);

    for (uint64_t i = 0; i < node->n_children; i++) {
        node_t *ident = node->children[i];
        assert(ident->type == IDENTIFIER_DATA);

        symbol_t *symb = ir_symbol_new(ident->data_char_ptr, strlen(ident->data_char_ptr),
                                       SYM_GLOBAL_VAR, node, -1, 0, NULL);
        PUSH_SYMBOL(ctx, symb);
        IR_INSERT_GLOBAL_SYMBOL(ctx, symb);
    }
}

/* ir_find_globals: Find globals (global variables and functions) by searching the ast. */
void ir_find_globals(ir_ctx_t *ctx, node_t *root)
{
    /* Global variables and functions has to be on the top level, directly below GLOBAL_LIST. */
    assert(root->n_children == 1);
    assert(root->type == PROGRAM);
    node_t *gl = root->children[0];

    for (uint64_t i = 0; i < gl->n_children; i++) {
        node_t *child = gl->children[i];
        if (child->type == FUNCTION) {
            add_function_symbol(ctx, child);

            /* NOTE: In my version DECLARATION_LIST is promoted to VARIABLE_LIST,
             * but since there makes no sense to have VARIABLE_LISTs which are not
             * DECLARATIONs then we know that this is a declaration list. */
        } else if (child->type == VARIABLE_LIST) {
            add_global_variable_list_symbol(ctx, child);
        }
    }
}

#define IR_INSERT_FUNC_LOCAL_SYMBOL(func, symb) \
    VEC_PUSH((func)->locals, symbol_t_ptr, symb)
    //assert(!tlhash_insert((func)->locals, (symb)->name, (symb)->name_len, (symb)))
    //assert(!tlhash_insert((func)->locals, (symb), sizeof((symb)), (symb)))

#define IR_INSERT_LOCAL_SYMBOL(locals, symb) \
    assert(!tlhash_insert(locals, (symb)->name, (symb)->name_len, (symb)))

static symbol_t *lookup_symb(ir_ctx_t *ctx, const char *key, size_t key_len)
{
    uint64_t l = VEC_LEN(&ctx->scopes);
    for (uint64_t i = 0; i < l; i++) {
        tlhash_t *locals = VEC_GET(&ctx->scopes, tlhash_t_ptr, l-i-1);
        assert(locals);

        symbol_t *out = NULL;
        if (!tlhash_lookup(locals, (void *) key, key_len, (void **) &out))
            return out;
    }
    return 0;
}

#define LOOKUP_IDENT(ctx, node)                                         \
    lookup_symb((ctx), (node)->data_char_ptr, strlen((node)->data_char_ptr))

/* Traverse the tree, assumes that parameters are initialized, but that locals ARE NOT. */
static void bind_recursive(ir_ctx_t *ctx, symbol_t *function, node_t *root, uint64_t *seq, uint32_t depth)
{
    symbol_t *temp = NULL;
    tlhash_t *temp_tbl = NULL;

    switch (root->type) {
        case BLOCK:
            //if (depth == 0) {
            //    /* Special case: want to push to the function scope, which is when depth = 0. */
            //    temp_tbl = function->locals;
            //} else {
            //    temp_tbl = xcalloc(1, sizeof(*temp_tbl));
            //    assert(!tlhash_init(temp_tbl, IR_LOCALS_TLHASH_BUCKETS));
            //    VEC_PUSH(&ctx->scopes, tlhash_t_ptr, temp_tbl);
            //}
            temp_tbl = xcalloc(1, sizeof(*temp_tbl));
            assert(!tlhash_init(temp_tbl, IR_LOCALS_TLHASH_BUCKETS));
            VEC_PUSH(&ctx->scopes, tlhash_t_ptr, temp_tbl);

            for (uint64_t i = 0; i < root->n_children; i++) {
                if (root->children[i]->type == VARIABLE_LIST || root->children[i]->type == DECLARATION_LIST) {
                    for (uint64_t k = 0; k < root->children[i]->n_children; k++) {
                        node_t *ident = root->children[i]->children[k];
                        assert(ident->type == IDENTIFIER_DATA);
                        symbol_t *symb = ir_symbol_new(ident->data_char_ptr, strlen(ident->data_char_ptr), SYM_LOCAL_VAR, ident, *seq, 0, NULL);
                        PUSH_SYMBOL(ctx, symb);
                        (*seq)++;
                        IR_INSERT_LOCAL_SYMBOL(VEC_PEEK(&ctx->scopes, tlhash_t_ptr), symb);
                        IR_INSERT_FUNC_LOCAL_SYMBOL(function, symb);
                    }
                    continue;
                }
                /* Recurse with the new scope as the current scope. */
                bind_recursive(ctx, function, root->children[i], seq, depth+1);
            }
            /* Special case: want to push to the function scope, which is when depth = 0. */
            //if (depth != 0) {
                /* Pop the new scope. */
                assert(temp_tbl == VEC_POP(&ctx->scopes, tlhash_t_ptr));
                tlhash_finalize(temp_tbl);
                free(temp_tbl);
            //}
            temp_tbl = NULL;
            break;

        case IDENTIFIER_DATA:
            if ((temp = LOOKUP_IDENT(ctx, root))) {
                root->entry = temp;
            } else {
                /* Unresolved symbol. */
                fprintf(stderr, "QUITTING: Unresolvable symbol `%s` at %d:%d\n", root->data_char_ptr, root->line, root->col);
                assert(0);
            }
            break;

        case STRING_DATA:
            root->entry_strings_index = VEC_LEN(&ctx->strings);
            VEC_PUSH(&ctx->strings, ir_str, root->data_char_ptr);
            break;

        default:
            for (uint64_t i = 0; i < root->n_children; i++)
                bind_recursive(ctx, function, root->children[i], seq, depth+1);
    }

}

void ir_bind_names(ir_ctx_t *ctx, symbol_t *function, node_t *root)
{
    assert(function->locals == NULL);
    function->locals = xcalloc(1, sizeof(*function->locals));
    assert(!VEC_INIT(function->locals, symbol_t_ptr));

    tlhash_t function_scope;
    memset(&function_scope, 0, sizeof(function_scope));
    assert(!tlhash_init(&function_scope, IR_LOCALS_TLHASH_BUCKETS));

    //function->locals = xcalloc(1, sizeof(*function->locals));
    //assert(!tlhash_init(function->locals, IR_LOCALS_TLHASH_BUCKETS));

    /* Params. */
    assert(root->n_children >= 2);
    assert(root->children[1]->type == VARIABLE_LIST);
    const node_t *params = root->children[1];
    for (uint64_t i = 0; i < params->n_children; i++) {
        symbol_t *symb = ir_symbol_new(params->children[i]->data_char_ptr,
                                       strlen(params->children[i]->data_char_ptr),
                                       SYM_PARAMETER, params->children[i], i, 0, NULL);
        PUSH_SYMBOL(ctx, symb);
        IR_INSERT_FUNC_LOCAL_SYMBOL(function, symb);
        IR_INSERT_LOCAL_SYMBOL(&function_scope, symb);
    }

    /* Push scopes. */
    VEC_PUSH(&ctx->scopes, tlhash_t_ptr, &ctx->names);
    VEC_PUSH(&ctx->scopes, tlhash_t_ptr, &function_scope);
    //VEC_PUSH(&ctx->scopes, tlhash_t_ptr, function->locals);

    uint64_t local_seq = 0;
    bind_recursive(ctx, function, root->children[2], &local_seq, 0);

    //VEC_POP(&ctx->scopes, tlhash_t_ptr); // function locals
    VEC_POP(&ctx->scopes, tlhash_t_ptr); // function scope
    VEC_POP(&ctx->scopes, tlhash_t_ptr); // global names

   tlhash_finalize(&function_scope);
}

void ir_print_symtab(ir_ctx_t *ctx, node_t *root)
{
    ir_print_symbols(ctx);
    ir_print_bindings(ctx, root);
}

void ir_print_symbols(ir_ctx_t *ctx)
{
    printf("String table:\n");
    for (size_t s = 0; s < VEC_LEN(&ctx->strings); s++)
        printf("%zu: %s\n", s, VEC_GET(&ctx->strings, ir_str, s));
    printf("-- \n");

    printf("Globals:\n");
    size_t n_globals = tlhash_size(&ctx->names);
    symbol_t *global_list[n_globals];
    tlhash_values (&ctx->names, (void **) &global_list);
    for (size_t g = 0; g < n_globals; g++) {
        switch (global_list[g]->type) {
            case SYM_FUNCTION:
                printf("%s: function %zu:\n", global_list[g]->name, global_list[g]->seq);
                if (global_list[g]->locals != NULL) {
                    //size_t localsize = tlhash_size(global_list[g]->locals);
                    //printf ("\t%zu local variables, %zu are parameters:\n", localsize, global_list[g]->nparms);
                    printf ("\t%zu local variables, %zu are parameters:\n", VEC_LEN(global_list[g]->locals), global_list[g]->nparms);
                    //symbol_t *locals[localsize];
                    //tlhash_values(global_list[g]->locals, (void **)locals );
                    for (size_t i = 0; i < VEC_LEN(global_list[g]->locals); i++) {
                        //printf("\t%s: ", locals[i]->name);
                        symbol_t *local = VEC_GET(global_list[g]->locals, symbol_t_ptr, i);
                        printf("\t%s: ", local->name);
                        switch(local->type) {
                            case SYM_PARAMETER: printf("parameter %zu\n", local->seq); break;
                            case SYM_LOCAL_VAR: printf("local var %zu\n", local->seq); break;
                            //case SYM_PARAMETER: printf("parameter %zu\n", locals[i]->seq); break;
                            //case SYM_LOCAL_VAR: printf("local var %zu\n", locals[i]->seq); break;
                            default: continue;
                        }
                    }
                }
                break;
            case SYM_GLOBAL_VAR:
                printf("%s: global variable\n", global_list[g]->name);
                break;
            default:
                break;
        }
    }
    printf("-- \n");
}

void ir_print_bindings(ir_ctx_t *ctx, node_t *root)
{
    if (root == NULL) return;
    else if (root->entry != NULL && root->type != STRING_DATA) {
        switch (root->entry->type) {
            case SYM_GLOBAL_VAR: printf("Linked global var '%s' [line:%d,col:%d:]\n",     root->entry->name, root->line, root->col); break;
            case SYM_FUNCTION:   printf("Linked function %zu ('%s') [line:%d,col:%d]\n",  root->entry->seq, root->entry->name, root->line, root->col); break;
            case SYM_PARAMETER:  printf("Linked parameter %zu ('%s') [line:%d,col:%d]\n", root->entry->seq, root->entry->name, root->line, root->col); break;
            case SYM_LOCAL_VAR:  printf("Linked local var %zu ('%s') [line:%d,col:%d]\n", root->entry->seq, root->entry->name, root->line, root->col); break;
            //case SYM_GLOBAL_VAR: printf("Linked global var '%s'\n",      root->entry->name); break;
            //case SYM_FUNCTION:   printf("Linked function %zu ('%s')\n",  root->entry->seq, root->entry->name); break;
            //case SYM_PARAMETER:  printf("Linked parameter %zu ('%s')\n", root->entry->seq, root->entry->name); break;
            //case SYM_LOCAL_VAR:  printf("Linked local var %zu ('%s')\n", root->entry->seq, root->entry->name); break;
        }
    } else if (root->type == STRING_DATA) {
        uint64_t string_max = root->entry_max; // NOTE: Modified.
        if (string_max < VEC_LEN(&ctx->strings)) printf("Linked string %zu\n", root->entry_strings_index); // NOTE: Modified.
        else printf("(Not an indexed string)\n");
    }
    for (size_t c = 0; c < root->n_children; c++)
        ir_print_bindings(ctx, root->children[c]);
}
