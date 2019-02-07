#include "tree.h"
#include "utils.h"

// NOTE: Changed from "destroy subtree" to "tree_destroy",
//       as a subtree is always tree itself.
void tree_destroy(node_t *n)
{
    for (uint64_t i = 0; i < n->n_children; i++) {
        tree_destroy(n->children[i]);
    }
    node_finalize(n);
}

// NOTE: Changed order of parameters
void tree_simplify(node_t *root, node_t **simplified_out)
{
    NOT_IMPLEMENTED(tree_simplify, "upcoming assignment");
}
