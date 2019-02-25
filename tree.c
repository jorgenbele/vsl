#include "tree.h"
#include "utils.h"

/* NOTE: Changed from "destroy subtree" to "tree_destroy",
 *       as a subtree is always tree itself. */
void tree_destroy(node_t *n)
{
    for (uint64_t i = 0; i < n->n_children; i++) {
        tree_destroy(n->children[i]);
        n->children[i] = NULL;
    }
    node_finalize(n);
}

typedef node_t *node_t_ptr;
DEF_VEC(node_t_ptr, node_t_ptr, NULL);

#define EVAL_CONST_EXPR1(op, left)                                      \
    node_new(NUMBER_DATA, ((void *) (uintptr_t) (int64_t) (op (left))), 0)

#define EVAL_CONST_EXPR2(left, op, right)                               \
    node_new(NUMBER_DATA, ((void *) (uintptr_t) (int64_t) ((left) op (right))), 0)

/* eval_const_expr(): Evaluate constant expressions,
 * for now only immediate integer arithmetic. */
static void eval_const_expr(node_t *root, vec_node_t_ptr *abandoned)
{
    if (!root) return;

    /* First recurse the children. */
    for (size_t i = 0; i < root->n_children; i++)
        eval_const_expr(root->children[i], abandoned);

    if (root->type != EXPRESSION) return;

    /* Make sure all children are constants (numbers for now). */
    for (size_t i = 0; i < root->n_children; i++)
        if (root->children[i]->type != NUMBER_DATA) return;

    int_type left = root->children[0]->data_integer;
    node_t *res = NULL;
    if (root->n_children == 1) {
        if (*root->data_char_ptr == '-') res = EVAL_CONST_EXPR1(-, left);
        else if (*root->data_char_ptr == '~') res = EVAL_CONST_EXPR1(~, left);
    } else {
        if (root->n_children != 2) {
            debug("n_children has to be 1 or 2 for const. exprs.!");
            exit(1);
        }

        int_type right = root->children[1]->data_integer;
        switch (*root->data_char_ptr) {
            case '+': { res = EVAL_CONST_EXPR2(left, +, right); break; }
            case '-': { res = EVAL_CONST_EXPR2(left, -, right); break; }
            case '*': { res = EVAL_CONST_EXPR2(left, *, right); break; }
            case '/': { res = EVAL_CONST_EXPR2(left, /, right); break; }
            default: {
                debug("Unknown const.expr op: %c", *root->data_char_ptr);
                exit(1);
                break;
            }
        }
    }

    node_t temp = *root;
    *root = *res;
    *res = temp;

    /* Abandon the previous root and nodes, which are now found in res. */
    for (size_t i = 0; i < res->n_children; i++)
        VEC_PUSH(abandoned, node_t_ptr, res->children[i]);

    VEC_PUSH(abandoned, node_t_ptr, res);

    return;
}

#undef EVAL_CONST_EXPR1
#undef EVAL_CONST_EXPR2

/* eliminate_inter(): Removes nodes that only contains one child and are
 * of no particular use, other than that they were useful for parsing.
 *
 * This includes:
 *    1. empty (no data) EXPRESSION nodes only containing one child,
 *    2. STATEMENT nodes only containing one child,
 */
static void eliminate_inter(node_t *root, vec_node_t_ptr *abandoned)
{
    if (!root) return;

    /* Remove empty expression nodes which only contain one child,
     * replacing it with its only child instead. */

    /* First recurse the children. */
    for (size_t i = 0; i < root->n_children; i++)
        eliminate_inter(root->children[i], abandoned);

    if ((root->n_children == 1)
        && ((root->type == EXPRESSION && !root->data) || root->type == STATEMENT)) {

        /* Swap root and child inplace. */
        node_t *child = root->children[0];
        root->children[0] = NULL;
        node_t temp = *root;
        *root = *child;
        *child = temp;

        VEC_PUSH(abandoned, node_t_ptr, child);
    }
}

/* flatten(): Flattens the tree by eliminating artifacts
 * from the parsing stage. Adds *_LIST children of compatible types
 * as children to the head *_LIST node, and adds the previously
 * unneeded nodes to 'abandoned'. */
static void flatten(node_t *root, vec_node_t_ptr *abandoned)
{
    if (!root) return;

    /* First flatten the children. */
    for (size_t i = 0; i < root->n_children; i++)
        flatten(root->children[i], abandoned);

    if (!node_is_list[root->type]) {
        /* Root node is not a list, so nothing more to do. */
        return;
    }

    /*
     * Root is list, try to merge all children lists of the
     * same type into root, and add the unused nodes to abandoned.
     */
    VEC(node_t_ptr) children;
    VEC_INIT(&children, node_t_ptr);

    if (root->n_children == 1
        && node_list_parents[root->children[0]->type] & NODE_TYPE_TO_FLAG(root->type)
        && (FLAG_KEEP_CHILDREN_TYPE & node_list_parents[root->children[0]->type])) {
        /* The FLAG_KEEP_CHILDREN_TYPE is set on the child, which is also compatible with
         * the root node. This means that we can swap the root node and the child node. */

         /* Invalidate the child pointer in the original root. */
        node_t *child = root->children[0];
        root->children[0] = NULL;

        /* Do the swap. */
        node_t temp = *root;
        *root = *child;
        *child = temp;

        VEC_PUSH(abandoned, node_t_ptr, child);
    } else {
        for (size_t i = 0; i < root->n_children; i++) {
            node_t_ptr child = root->children[i];
            if (node_list_parents[root->children[i]->type] & NODE_TYPE_TO_FLAG(root->type)) {
                /* Root and current child are compatible. Merge children of
                 * the current child with the root list. */
                for (size_t j = 0; j < child->n_children; j++) {
                    VEC_PUSH(&children, node_t_ptr, child->children[j]);
                    /* Invalidate pointer in the original array. */
                    child->children[j] = NULL;
                }
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
}

/* NOTE: Changed order of parameters */
void tree_simplify(node_t *root)
{
    /* Store the nodes no longer needed in a vector for later use. */
    vec_node_t_ptr abandoned;
    VEC_INIT(&abandoned, node_t_ptr);

    flatten(root, &abandoned);
    eliminate_inter(root, &abandoned);
    eval_const_expr(root, &abandoned);

    /* Destroy the abandoned nodes. */
    while (VEC_LEN(&abandoned) >= 1 && !VEC_ERROR(&abandoned))
        node_finalize(VEC_POP(&abandoned, node_t_ptr));
    VEC_DESTROY(&abandoned, node_t_ptr);
}
