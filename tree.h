#ifndef __TREE_H_
#define __TREE_H_

#include "node.h"
#include "vec.h"

#define destroy_subtree(discard) tree_destroy((discard))
#define simplify_tree(simplified_out, root) tree_simplify((root), (simplified_out))

void tree_destroy(node_t *discard);

// NOTE: Changed order of parameters
//void tree_simplify(node_t *root, node_t **simplified_out);
void tree_simplify(node_t *root);


typedef int (*tree_extract_function_t)(const node_t *node, int depth);
int tree_extract_by(node_t *root, tree_extract_function_t do_extract_func, VEC(node_t_ptr) *collected);


#endif // __TREE_H_
