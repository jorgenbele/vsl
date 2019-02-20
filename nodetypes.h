#ifndef __NODETYPES_H_
#define __NODETYPES_H_

#include <stdbool.h>
#include <stdint.h>

/*
 * Enumeration of node types.
 */
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

#define NODE_TYPE_TO_FLAG(type) ((uint32_t) (1<<((type)+1)))

/* Node types as flags.
 * The above table is not specified as flags because that would make
 * the lookup tables large. */
enum node_flag {
    FLAG_PROGRAM               = (uint32_t)  1<<1,
    FLAG_GLOBAL_LIST           = (uint32_t)  1<<2,
    FLAG_GLOBAL                = (uint32_t)  1<<3,
    FLAG_STATEMENT_LIST        = (uint32_t)  1<<4,
    FLAG_PRINT_LIST            = (uint32_t)  1<<5,
    FLAG_EXPRESSION_LIST       = (uint32_t)  1<<6,
    FLAG_VARIABLE_LIST         = (uint32_t)  1<<7,
    FLAG_ARGUMENT_LIST         = (uint32_t)  1<<8,
    FLAG_PARAMETER_LIST        = (uint32_t)  1<<9,
    FLAG_DECLARATION_LIST      = (uint32_t) 1<<10,
    FLAG_FUNCTION              = (uint32_t) 1<<11,
    FLAG_STATEMENT             = (uint32_t) 1<<12,
    FLAG_BLOCK                 = (uint32_t) 1<<13,
    FLAG_ASSIGNMENT_STATEMENT  = (uint32_t) 1<<14,
    FLAG_RETURN_STATEMENT      = (uint32_t) 1<<15,
    FLAG_PRINT_STATEMENT       = (uint32_t) 1<<16,
    FLAG_NULL_STATEMENT        = (uint32_t) 1<<17,
    FLAG_IF_STATEMENT          = (uint32_t) 1<<18,
    FLAG_WHILE_STATEMENT       = (uint32_t) 1<<19,
    FLAG_EXPRESSION            = (uint32_t) 1<<20,
    FLAG_RELATION              = (uint32_t) 1<<21,
    FLAG_DECLARATION           = (uint32_t) 1<<22,
    FLAG_PRINT_ITEM            = (uint32_t) 1<<23,
    FLAG_IDENTIFIER_DATA       = (uint32_t) 1<<24,
    FLAG_NUMBER_DATA           = (uint32_t) 1<<25,
    FLAG_STRING_DATA           = (uint32_t) 1<<26,
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
extern const char *node_type_to_string[LAST_NO_TYPE];

/* lookup table: node type has printable data */
extern const bool node_tpr_data[LAST_NO_TYPE];

/* lookup table: node type has malloc'ed data */
extern const bool node_malloc_data[LAST_NO_TYPE];

extern const bool node_is_list[LAST_NO_TYPE];

/* lookup table: which node types a given node type can merge
 * its children with in tree_simplify(). The table consists
 * of a set of flags for each node type, specifying whether
 * it can be transformed into that node, or not.
 *
 * Example:
 *     node_list_parents[PRINT_ITEM] & PRINT_LIST != 0
 *   means that the following transision is allowed:
 *
 *    PRINT_LIST                 PRINT_LIST
 *       PRINT_ITEM         =>      "Hello, World"
 *         "Hello, World"
 *
 *     node_list_parent[PRINT_LIST] & PRINT_LIST != 0
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
extern const uint32_t node_list_parents[LAST_NO_TYPE];

/*
 * lookup table: used to convert from node type to flag,
 * currently not used as the NODE_TYPE_TO_FLAG macro can be
 * used instead..
 */
extern const enum node_flag node_type_to_flag[LAST_NO_TYPE];

#endif // __NODETYPES_H_
