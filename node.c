#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>
#include <string.h>

#include "node.h"
#include "tree.h"
#include "utils.h"

/* Vector types. */
DEF_VEC_FUNCS(node_t_ptr, node_t_ptr, NULL);

/* node_print(): Recursively print the tree from 'root'. */
void node_print(const node_t *root, int nesting)
{
    if (root != NULL) {
        /* Print the type of node indented by the nesting level */
    #if DEBUG
        printf("%*ctype: %s, n_children: %d", nesting, ' ', NODE_TO_TYPE_STRING(root), root->n_children);
    #else
        printf("%*c%s", nesting, ' ', NODE_TO_TYPE_STRING(root));
    #endif

        /* For identifiers, strings, expressions and numbers,
         * print the data element also
         */
        if (NODE_HAS_PRINTABLE_DATA(root)) {
        #if DEBUG
            printf(", data: (%s)", STR_OR_NULL((char *) root->data_char_ptr));
        #else
            printf("(%s)", STR_OR_NULL((root->data_char_ptr)));
        #endif
        } else if (root->type == NUMBER_DATA) {
            /*
             * NOTE: No need to store a pointer to int64_t (int_type) in root->data, when
             *       on 64-bits systems (which this compiler is made for) have
             *       pointers with size of 8 bytes. Uses the PRIdit macro (in nodetypes.h)
             *       to specify the correct printf specifier for int64_t.
             */
        #if DEBUG
            printf(", data: (%" PRIdit ")", root->data_integer);
        #else
            printf("(%" PRIdit ")",  root->data_integer);
        #endif
        }

        #if DEBUG
        if (root->comment) {
            printf("[%s]", root->comment->data_char_ptr);
        }
        #endif

        /* Make a new line, and traverse the node's children in the same manner */
        putchar('\n');
        for (uint64_t i = 0; i < root->n_children; i++) {
            node_print(root->children[i], nesting+1);
        }
    } else {
        printf("%*c%p\n", nesting, ' ', (void *) root);
    }
}

#define VA_LIST_NODE_INIT(n, type, data, n_children, ap)            \
    do {                                                            \
        n->type = type;                                             \
        n->data = data;                                             \
        n->n_children = n_children;                                 \
        n->comment = NULL;  /* Is set by the parser. */             \
                                                                    \
        n->children = xcalloc(n_children, sizeof(*n->children));    \
                                                                    \
        n->entry_max = 0;                                           \
                                                                    \
        for (uint64_t i = 0; i < n_children; i++) {                 \
            n->children[i] = va_arg(ap, node_t *);                  \
        }                                                           \
    } while (0)

/* node_init(): Assigns the given values to the given node (allocates children array). */
void node_init(node_t *n, enum node_type type, void *data, uint64_t n_children, ...)
{
    va_list ap;
    va_start(ap, n_children);
    VA_LIST_NODE_INIT(n, type, data, n_children, ap);
    va_end(ap);
}

/* node_new(): Allocate and initialize a new node. */
node_t *node_new(enum node_type type, void *data, uint64_t n_children, ...)
{
    //debug("CREATING NEW NODE: type: %s, data: %s\n", node_t2s[type], node_tpr_data[type] ? (char *) data : "");
    va_list ap;
    va_start(ap, n_children);
    node_t *n = xcalloc(1, sizeof(*n));
    VA_LIST_NODE_INIT(n, type, data, n_children, ap);
    va_end(ap);
    return n;
}

/* node_new(): Allocate and initialize a new node. WITH LINE AND COLUMN NUMBERS! */
node_t *node_new_lc(enum node_type type, void *data, int line, int col, uint64_t n_children, ...)
{
    //debug("CREATING NEW NODE: type: %s, data: %s\n", node_t2s[type], node_tpr_data[type] ? (char *) data : "");
    va_list ap;
    va_start(ap, n_children);
    node_t *n = xcalloc(1, sizeof(*n));
    VA_LIST_NODE_INIT(n, type, data, n_children, ap);
    va_end(ap);
    n->line = line;
    n->col = col;
    return n;
}

#undef VA_LIST_NODE_INIT

/* Does not set the type. */
void node_dup_data(node_t dest[static 1], const node_t src[static 1])
{
    if (!NODE_MALLOC_DATA(src)) {
        dest->data_max = src->data_max;
        return;
    }

    if (NODE_HAS_PRINTABLE_DATA(src)) {
        /* String */
        dest->data_char_ptr = strdup(src->data_char_ptr);
        return;
    } else {
        debug("Incompatible arguments to node_dup_data!");
        exit(1);
    }

    if (src->comment) {
        /* The node has a comment attached. Duplicate it. */
        if (!dest->comment) xcalloc(1, sizeof(*dest->comment));
        node_dup_data(dest->comment, src->comment);
    }
}

/* Remove a node and its contents */
/* node_finalize():  */
void node_finalize(node_t n[static 1])
{
    free(n->children);
    if (n->comment) node_finalize(n->comment);
    if (n->original) tree_destroy(n->original);
    if (NODE_MALLOC_DATA(n)) free(n->data);
    free(n);
}
