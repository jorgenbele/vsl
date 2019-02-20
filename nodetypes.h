#ifndef __NODETYPES_H_
#define __NODETYPES_H_

#include <stdbool.h>
#include <stdint.h>

enum node_type {
    PROGRAM              =  0,
    GLOBAL_LIST          =  1,
    GLOBAL               =  2,
    STATEMENT_LIST       =  3,
    PRINT_LIST           =  4,
    EXPRESSION_LIST      =  5,
    VARIABLE_LIST        =  6,
    ARGUMENT_LIST        =  7,
    PARAMETER_LIST       =  8,
    DECLARATION_LIST     =  9,
    FUNCTION             = 10,
    STATEMENT            = 11,
    BLOCK                = 12,
    ASSIGNMENT_STATEMENT = 13,
    RETURN_STATEMENT     = 14,
    PRINT_STATEMENT      = 15,
    NULL_STATEMENT       = 16,
    IF_STATEMENT         = 17,
    WHILE_STATEMENT      = 18,
    EXPRESSION           = 19,
    RELATION             = 20,
    DECLARATION          = 21,
    PRINT_ITEM           = 22,
    IDENTIFIER_DATA      = 23,
    NUMBER_DATA          = 24,
    STRING_DATA          = 25,

    /* Used to get the number of different node types. */
    LAST_NO_TYPE         = 26
};

/* typedef for the integer type to use in the compiler */
typedef int64_t int_type;

/*
 * Platform independent print format specifier.
 * Used since long is 64 bits on some systems, while
 * long is 32 bits and long long is 64 bits on some other
 * systems.
 */
/* for printf */
#define PRIdit PRId64

/* for scanf  */
#define SCNdit SCNd64

/* Macro used to cast from any pointer/pointer-sized data
 * type to (void *) without losing the ability to cast
 * back to the original type. */
#define NODE_DATA_CAST (void *)(uintptr_t)

/* lookup table: node type to type string     */
extern const char *node_t2s[LAST_NO_TYPE];

/* lookup table: node type has printable data */
extern const bool node_tpr_data[LAST_NO_TYPE];

/* lookup table: node type has malloc'ed data */
extern const bool node_malloc_data[LAST_NO_TYPE];

extern const bool node_is_list[LAST_NO_TYPE];

/* lookup table: which node type a given node type can merge
 * its children with in tree_simplify().
 *
 * Example:
*      node_list_parent[PRINT_ITEM] = PRINT_LIST
 *   means that the following transision is allowed:
 *
 *    PRINT_LIST                 PRINT_LIST
 *       PRINT_ITEM         =>      "Hello, World"
 *         "Hello, World"
 *
 *     node_list_parent[PRINT_LIST] = PRINT_LIST
 *   means that the following transition is allowed:
 *
 *    PRINT_LIST                 PRINT_LIST
 *      PRINT_LIST                 "Hello, "
 *        PRINT_LIST               "this is"
 *          PRINT_ITEM             "Mike"
 *            "Mike"      =>
 *        PRINT_ITEM
 *          "this is"
 *      PRINT_ITEM
 *        "Hello, "
 */
extern const enum node_type node_list_parent[LAST_NO_TYPE];

#endif // __NODETYPES_H_
