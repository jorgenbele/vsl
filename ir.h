#ifndef __IR_H_
#define __IR_H_

#include "tlhash.h"

#include "node.h"
#include "vec.h"

struct node;

typedef char * ir_str;
DEF_VEC_HEADER(ir_str, ir_str);

typedef tlhash_t *tlhash_t_ptr;
DEF_VEC_HEADER(tlhash_t_ptr, tlhash_t_ptr);

struct symbol;
typedef struct symbol symbol_t;
typedef symbol_t *symbol_t_ptr;
DEF_VEC_HEADER(symbol_t_ptr, symbol_t_ptr);

typedef enum {
    SYM_GLOBAL_VAR, SYM_FUNCTION, SYM_PARAMETER, SYM_LOCAL_VAR
} symtype_t;

struct symbol {
    char     *name;
    size_t    name_len;
    symtype_t type;
    node_t   *node;
    size_t    seq;
    size_t    nparms;

    /* MODIFIED: Use a vector instead of a hashtable.
     * The sequence number is the index into this table. */
    VEC(symbol_t_ptr) *locals;
};

typedef uint64_t label_t;
DEF_VEC_HEADER(label_t, label_t);

/*
 * Use and pass a context struct instead of using global variables.
 */
typedef struct {
    /* Hash table: (char *)name -> symbol_t. */
    tlhash_t names;
    /* Use a vector of instead of a manually extended dynamic-array. */
    VEC(ir_str) strings;

    symbol_t **temp; /* Used for temporary storage of symbols. */
    size_t temp_size;

    VEC(tlhash_t_ptr) scopes;
    VEC(symbol_t_ptr) symbols;

    uint64_t seq; /* Sequence count. */
    uint64_t label_count; /* Used in code generation. */

    uint64_t func_stack_aligned;
    VEC(label_t) labels;

    bool export_functions;
    bool generate_main;
    bool generate_header;
} ir_ctx_t;

void ir_ctx_init(ir_ctx_t *ctx);
void ir_ctx_destroy(ir_ctx_t *ctx);


void ir_create_symtab(ir_ctx_t *ctx, node_t *root);
void ir_symbol_destroy(symbol_t *symb);

void ir_create_symtab(ir_ctx_t *ctx, node_t *root); /* void create_symbol_table(void); */
void ir_print_symtab(ir_ctx_t *ctx, node_t *root);  /* void print_symbol_table(void);  */
void ir_print_symbols(ir_ctx_t *ctx); /* void print_symbols(void); */

void ir_print_bindings(ir_ctx_t *ctx, node_t *root);                  /* void print_bindings(node_t *root); */
void ir_destroy_symtab(ir_ctx_t *ctx);                                /* void destroy_symbol_table(void); */
void ir_find_globals(ir_ctx_t *ctx, node_t *root);                                  /* void find_globals(void); */
void ir_bind_names(ir_ctx_t *ctx, symbol_t *function, node_t *root);  /* void bind_names(symbol_t *function, node_t *root); */
void ir_destroy_symtab(ir_ctx_t *ctx);                                /* void destroy_symtab(void); */

#endif // __IR_H_
