#ifndef __TREE_H_
#define __TREE_H_

#include "node.h"

#define destroy_subtree(discard) tree_destroy((discard))
#define simplify_tree(simplified_out, root) tree_simplify((root), (simplified_out))

void tree_destroy(node_t *discard);

// NOTE: Changed order of parameters
void tree_simplify(node_t *root, node_t **simplified_out);


#endif // __TREE_H_
