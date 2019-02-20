#include "tree.h"
#include "utils.h"

//const node_t vec_default_node_t = {0};
//DEF_VEC_FUNCS(node_t, node_t, vec_default_node_t);

// NOTE: Changed from "destroy subtree" to "tree_destroy",
//       as a subtree is always tree itself.
void tree_destroy(node_t *n)
{
    for (uint64_t i = 0; i < n->n_children; i++) {
        tree_destroy(n->children[i]);
        n->children[i] = NULL;
    }
    node_finalize(n);
}

/*
 * Transforms the tree from:
 * ...
 * TYPE_LIST
 *    TYPE_LIST
 *       TYPE_LIST
 *          ...
 *          ELEM
 *       ELEM
 *    ELEM
 *
 * to:
 * ...
 * TYPE_LIST
 *    ...
 *    ELEM
 *    ELEM
 *    ELEM
 *
 */


/*
  Algorithm:

  flatten(up, cur):
     if up is list and cur is list:
        add children of cur to children of up
 */


typedef node_t *node_t_ptr;
DEF_VEC(node_t_ptr, node_t_ptr, NULL);

static void flatten(node_t *root, vec_node_t_ptr *abandoned, int depth)
{
    if (!root) return;

    /* First flatten the children. */
    for (size_t i = 0; i < root->n_children; i++)
        flatten(root->children[i], abandoned, depth + 4);

    if (!node_is_list[root->type]) {
        /* Root node is not a list, so nothing more to do. */
        return;
    }

    /*
     * Root is list, try to merge all children lists of the
     * same type into root, and add the unused nodes to abandoned.
     */
    vec_node_t_ptr children;
    VEC_INIT(&children, node_t_ptr);

    debug("%*cFlattening: type: %s, data: %s\n", depth, ' ', node_t2s[root->type], node_tpr_data[root->type] ? (char *) root->data_char_ptr : "");

    for (size_t i = 0; i < root->n_children; i++) {
        node_t_ptr child = root->children[i];
        if (node_list_parent[root->children[i]->type] == root->type) {
            debug("%*c==> [%lu] merging node: type: %s, data: %s\n", depth, ' ', i, node_t2s[child->type], node_tpr_data[child->type] ? (char *) child->data_char_ptr : "");

            /* Root and current child are compatible. Merge children of
             * the current child with the root list. */
            for (size_t j = 0; j < child->n_children; j++) {
                __auto_type child_c = child->children[j];
                debug("%*c==> ==> [%lu] pushing children: type: %s, data: %s\n", depth, ' ', i, node_t2s[child_c->type], node_tpr_data[child_c->type] ? (char *) child_c->data_char_ptr : "");
                VEC_PUSH(&children, node_t_ptr, child->children[j]);
                /* Invalidate pointer in the original array. */
                child->children[j] = NULL;
            }

            debug("%*c==> [%lu] abandoning node: type: %s, data: %s\n", depth, ' ', i, node_t2s[child->type], node_tpr_data[child->type] ? (char *) child->data_char_ptr : "");

            /* Push the invalidated node to abandoned vector. */
            VEC_PUSH(abandoned, node_t_ptr, child);
        } else {
            /* No change.  */
            VEC_PUSH(&children, node_t_ptr, child);
        }
    }

    free(root->children);
    root->children = VEC_ARRAY_PTR(&children);
    root->n_children = VEC_LEN(&children);
    /* NOTE: Does not destroy the vector data! */
}

// NOTE: Changed order of parameters
void tree_simplify(node_t *root, node_t **simplified_out)
{
    //(void) root; (void) simplified_out;
    //NOT_IMPLEMENTED(tree_simplify, "upcoming assignment");
    //*simplified_out = NULL;

    vec_node_t_ptr abandoned;
    VEC_INIT(&abandoned, node_t_ptr);

    flatten(root, &abandoned, 0);

    while (VEC_LEN(&abandoned) >= 1 && !VEC_ERROR(&abandoned)) {
        __auto_type child = VEC_PEEK(&abandoned, node_t_ptr);
        debug("finalizing node: type: %s, data: %s\n", node_t2s[child->type], node_tpr_data[child->type] ? (char *) child->data_char_ptr : "");
        node_finalize(VEC_POP(&abandoned, node_t_ptr));
    }
    VEC_DESTROY(&abandoned, node_t_ptr);
}
