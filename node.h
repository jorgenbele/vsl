#ifndef __NODE_H_
#define __NODE_H_

#include <stdlib.h>
#include <stdint.h>

#include "nodetypes.h"
#include "vec.h"

typedef struct node {
    enum node_type type;

    int line, col;

    /* Changed to use union instad of
     * potentially dangerous casting. */
    union {
        uintmax_t data_max;
        void *data;
        int_type data_integer;
        char *data_char_ptr;
    };

    struct node *comment; /* For functions (for now). */

    void *entry;
    uint64_t n_children;
    struct node **children;
} node_t;

/* Vector types. */
typedef node_t *node_t_ptr;
DEF_VEC_HEADER(node_t_ptr, node_t_ptr);


void node_init(node_t *n, enum node_type type, void *data, uint64_t n_childs, ...);
node_t *node_new(enum node_type type, void *data, uint64_t n_childs, ...);
node_t *node_new_lc(enum node_type type, void *data, int line, int col, uint64_t n_children, ...);
void node_dup_data(node_t *dest, const node_t *src);
void node_print(node_t *root, int nesting);
void node_finalize(node_t *discard);

/*
 * NOTE: The following functions are found in tree.h
 * void destroy_subtree(node_t *discard);
 * void node_destroy_subtree(node_t *discard);
 * void simplify_tree(node_t **simplified, node_t *root);
 */

/*
 * Macros to make sure an erronous node type does not cause the
 * compiler to go out of bounds.
 */

/* Converts a node to the string representation of its type. */
#define NODE_TO_TYPE_STRING(node)                                       \
    (((node)->type < LAST_NO_TYPE) ? ((node_type_to_string[(node)->type])) : "INVALID_TYPE")

/* Evaluates to true if the node has printable data. */
#define NODE_HAS_PRINTABLE_DATA(node)                                   \
    (((node)->type < LAST_NO_TYPE) ? ((node_tpr_data[(node)->type])) : 0)

/* Evaluates to true if the node has malloc'ed data
   (and thus needs to be freed upon completion). */
#define NODE_MALLOC_DATA(node)                                          \
    (((node)->type < LAST_NO_TYPE) ? ((node_malloc_data[(node)->type])) : 0)

/* Explicit conversion to "(null)" if str is NULL */
#define STR_OR_NULL(str) ((str) ? (str) : "(null)")

#endif /* __NODE_H_ */
