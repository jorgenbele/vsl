#ifndef __NODE_H_
#define __NODE_H_

#include <stdlib.h>
#include <stdint.h>

#include "nodetypes.h"

typedef struct node {
    enum node_type type;
    void *data;
    void *entry;
    uint64_t n_children;
    struct node **children;
} node_t;

void node_init(node_t *n, enum node_type type, void *data, uint64_t n_childs, ...);
node_t *node_new(enum node_type type, void *data, uint64_t n_childs, ...);
void node_print(node_t *root, int nesting);
void node_finalize(node_t *discard);

// NOTE: Found in tree.h
//void destroy_subtree(node_t *discard);
//void node_destroy_subtree(node_t *discard);
//void simplify_tree(node_t **simplified, node_t *root);

#define NODE_TO_TYPE_STRING(node) (((node)->type < LAST_NO_TYPE) ? ((node_t2s[(node)->type])) : "INVALID_TYPE")
#endif // __NODE_H_
