#ifndef __NODETYPES_H_
#define __NODETYPES_H_

#include <stdbool.h>
#include <stdint.h>

/*
 * There are two rule sets; one which I will use in the rest of the compiler project,
 * and is currently used in the source recreation (node_src.c, node_python.c), and
 * one which matches the tree.correct files (which were released AFTER i created mine).
 */
//#define USE_TREE_CORRECT_RULES

#define __NODE_TYPE_LIST                                        \
        X(PROGRAM              ,  0),                           \
        X(GLOBAL_LIST          ,  1),                           \
        X(GLOBAL               ,  2),                           \
        X(STATEMENT_LIST       ,  3),                           \
        X(PRINT_LIST           ,  4),                           \
        X(EXPRESSION_LIST      ,  5),                           \
        X(VARIABLE_LIST        ,  6),                           \
        X(ARGUMENT_LIST        ,  7),                           \
        X(PARAMETER_LIST       ,  8),                           \
        X(DECLARATION_LIST     ,  9),                           \
        X(FUNCTION             , 10),                           \
        X(STATEMENT            , 11),                           \
        X(BLOCK                , 12),                           \
        X(ASSIGNMENT_STATEMENT , 13),                           \
        X(RETURN_STATEMENT     , 14),                           \
        X(PRINT_STATEMENT      , 15),                           \
        X(NULL_STATEMENT       , 16),                           \
        X(IF_STATEMENT         , 17),                           \
        X(WHILE_STATEMENT      , 18),                           \
        X(EXPRESSION           , 19),                           \
        X(RELATION             , 20),                           \
        X(DECLARATION          , 21),                           \
        X(PRINT_ITEM           , 22),                           \
        X(IDENTIFIER_DATA      , 23),                           \
        X(NUMBER_DATA          , 24),                           \
        X(STRING_DATA          , 25),                           \
                                                                \
        X(BREAK_STATEMENT      , 26),                           \
                                                                \
                                                                \
    /* Python like doc-strings that are attached to function    \
     * nodes (node.comment).                                    \
     * Does not change the ast), so it can be ignored. */       \
        X(FUNCTION_COMMENT     , 27),                           \
                                                                \
        /* Used to get the number of different node types. */   \
        X(LAST_NO_TYPE         , 28)                            \


/*
 * Enumeration of node types.
 */
#define X(name, value) \
    name = value
enum node_type {
    __NODE_TYPE_LIST
};
#undef X

#define NODE_TYPE_IS_STATEMENT(type)                                    \
    ((FLAG_ASSIGNMENT_STATEMENT | FLAG_STATEMENT                        \
      | FLAG_RETURN_STATEMENT | FLAG_PRINT_STATEMENT | FLAG_NULL_STATEMENT \
      | FLAG_IF_STATEMENT | FLAG_WHILE_STATEMENT) & NODE_TYPE_TO_FLAG((type)))

#define NODE_TYPE_IS_EXPRESSION(type)                                   \
    ((FLAG_EXPRESSION | FLAG_IDENTIFIER_DATA | FLAG_NUMBER_DATA | FLAG_STRING_DATA) \
     & NODE_TYPE_TO_FLAG((type)))

#define NODE_TYPE_TO_FLAG(type) ((uint32_t) (1<<((type)+1)))

#define N_NODE_FLAGS (LAST_NO_TYPE+1)

#define __NODE_FLAG(type) FLAG_##type = NODE_TYPE_TO_FLAG(type)

/* Node types as flags.
 * The above table is not specified as flags because that would make
 * the lookup tables large. */
#define X(name, value) \
    __NODE_FLAG(name)

enum node_flag {
    __NODE_TYPE_LIST,

    FLAG__UNUSED            = NODE_TYPE_TO_FLAG(LAST_NO_TYPE),
    FLAG_KEEP_CHILDREN_TYPE = NODE_TYPE_TO_FLAG(LAST_NO_TYPE) + 1,
};
#undef X

#undef __NODE_FLAG

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
extern const char *node_type_to_string[LAST_NO_TYPE+1];

/* lookup table: node type has printable data */
extern const bool node_tpr_data[LAST_NO_TYPE+1];

/* lookup table: node type has malloc'ed data */
extern const bool node_malloc_data[LAST_NO_TYPE+1];

/* lookup table: is then node type a list type or not */
extern const bool node_is_list[LAST_NO_TYPE+1];

/* lookup table: which node types a given node type can merge
 * its children with in tree_simplify(). The table consists
 * of a set of flags for each node type, specifying whether
 * it can be merged into that node, or not.
 *
 * Also, the FLAG_KEEP_CHILDREN_TYPE flag specifies whether the
 * root (with a single children node) can be replaced by its child.
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
extern const uint32_t node_list_parents[LAST_NO_TYPE+1];

/*
 * lookup table: used to convert from node type to flag,
 * currently not used as the NODE_TYPE_TO_FLAG macro can be
 * used instead..
 */
extern const enum node_flag node_type_to_flag[N_NODE_FLAGS];

#endif /* ifndef __NODETYPES_H_ */
