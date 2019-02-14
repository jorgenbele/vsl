#include <stdio.h>
#include <stdarg.h>

#include "node.h"
#include "utils.h"

#define NODE_HAS_PRINTABLE_DATA(node) (((node)->type < LAST_NO_TYPE) ? ((node_tpr_data[(node)->type])) : 0)
#define NODE_MALLOC_DATA(node) (((node)->type < LAST_NO_TYPE) ? ((node_malloc_data[(node)->type])) : 0)

#define STR_OR_NULL(str) (str ? str : "NULL")

#if DEBUG
/* node_print(): Recursively print the tree from 'root'. */
void node_print(node_t *root, int nesting)
{
    if (root != NULL) {
        /* Print the type of node indented by the nesting level */
        printf("%*ctype: %s, n_children: %d", nesting, ' ', NODE_TO_TYPE_STRING(root), root->n_children);

        /* For identifiers, strings, expressions and numbers,
         * print the data element also
         */
        if (NODE_HAS_PRINTABLE_DATA(root)) {
            printf(", data: (%s)", STR_OR_NULL((char *) root->data));
        } else if (root->type == NUMBER_DATA) {
            //printf(", data: (%ld)", *((int64_t *)root->data));
            printf(", data: (%ld)", (int64_t)root->data);
        }

        /* Make a new line, and traverse the node's children in the same manner */
        putchar('\n');
        for (uint64_t i = 0; i < root->n_children; i++) {
            node_print(root->children[i], nesting+1);
        }
    } else {
        printf("%*c%p\n", nesting, ' ', root);
    }
}
#else
/* node_print(): Recursively print the tree from 'root'. */
void node_print(node_t *root, int nesting)
{
    if (root != NULL) {
        /* Print the type of node indented by the nesting level */
        printf("%*c%s", nesting, ' ', NODE_TO_TYPE_STRING(root));

        /* For identifiers, strings, expressions and numbers,
         * print the data element also
         */
        if (NODE_HAS_PRINTABLE_DATA(root)) {
            printf("(%s)", STR_OR_NULL((char *) root->data));
        } else if (root->type == NUMBER_DATA) {
            //printf("(%ld)", *((int64_t *)root->data));
            printf("(%ld)", (int64_t)root->data);
        }

        /* Make a new line, and traverse the node's children in the same manner */
        putchar('\n');
        for (uint64_t i = 0; i < root->n_children; i++) {
            node_print(root->children[i], nesting+1);
        }
    } else {
        printf("%*c%p\n", nesting, ' ', root);
    }
}
#endif

/* node_print_source(): Recursively print the tree from 'root'. */
void node_print_source(node_t *root, int nesting)
{
    if (root != NULL) {
        /* Print the type of node indented by the nesting level */
        printf("%*c%s", nesting, ' ', NODE_TO_TYPE_STRING(root));

        /* For identifiers, strings, expressions and numbers,
         * print the data element also
         */
        if (NODE_HAS_PRINTABLE_DATA(root)) {
            printf("(%s)", STR_OR_NULL((char *) root->data));
        } else if (root->type == NUMBER_DATA) {
            //printf("(%ld)", *((int64_t *)root->data));
            printf("(%ld)", (int64_t)root->data);
        }

        /* Make a new line, and traverse the node's children in the same manner */
        putchar('\n');
        for (uint64_t i = 0; i < root->n_children; i++) {
            node_print(root->children[i], nesting+1);
        }
    } else {
        printf("%*c%p\n", nesting, ' ', root);
    }
}

/* vnode_init(): va_list version of node_init(). */
static void vnode_init(node_t *n, enum node_type type, void *data, uint64_t n_children, va_list ap)
{
    n->type = type;
    n->data = data;
    n->n_children = n_children;

    n->children = xcalloc(n_children, sizeof(*n->children));

    for (uint64_t i = 0; i < n_children; i++) {
        n->children[i] = va_arg(ap, node_t *);
    }
}

/* node_init(): Assigns the given values to the given node. */
void node_init(node_t *n, enum node_type type, void *data, uint64_t n_children, ...)
{
    va_list ap;
    va_start(ap, n_children);
    vnode_init(n, type, data, n_children, ap);
    va_end(ap);
}

/* node_new(): Allocate and initialize a new node. */
node_t *node_new(enum node_type type, void *data, uint64_t n_children, ...)
{
    debug("CREATING NEW NODE: type: %s, data: %s\n", node_t2s[type], node_tpr_data[type] ? (char *) data : "");
    va_list ap;
    va_start(ap, n_children);
    node_t *n = xcalloc(1, sizeof(*n));
    vnode_init(n, type, data, n_children, ap);
    va_end(ap);
    return n;
}

/* Remove a node and its contents */
/* node_finalize():  */
void node_finalize(node_t *n)
{
    free(n->children);
    // TODO: Handle data and entry
    //if (NODE_MALLOC_DATA(n)) free(n->data);
    //free(n);
}
