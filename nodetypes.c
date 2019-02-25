#include "node.h"
#include "nodetypes.h"

#define AS_STR(x) #x

const char *node_type_to_string[LAST_NO_TYPE] = {
    AS_STR(PROGRAM),
    AS_STR(GLOBAL_LIST),
    AS_STR(GLOBAL),
    AS_STR(STATEMENT_LIST),
    AS_STR(PRINT_LIST),
    AS_STR(EXPRESSION_LIST),
    AS_STR(VARIABLE_LIST),
    AS_STR(ARGUMENT_LIST),
    AS_STR(PARAMETER_LIST),
    AS_STR(DECLARATION_LIST),
    AS_STR(FUNCTION),
    AS_STR(STATEMENT),
    AS_STR(BLOCK),
    AS_STR(ASSIGNMENT_STATEMENT),
    AS_STR(RETURN_STATEMENT),
    AS_STR(PRINT_STATEMENT),
    AS_STR(NULL_STATEMENT),
    AS_STR(IF_STATEMENT),
    AS_STR(WHILE_STATEMENT),
    AS_STR(EXPRESSION),
    AS_STR(RELATION),
    AS_STR(DECLARATION),
    AS_STR(PRINT_ITEM),
    AS_STR(IDENTIFIER_DATA),
    AS_STR(NUMBER_DATA),
    AS_STR(STRING_DATA),
    AS_STR(FUNCTION_COMMENT),
};

const bool node_tpr_data[LAST_NO_TYPE] = {
    0,    // PROGRAM
    0,    // GLOBAL_LIST
    0,    // GLOBAL
    0,    // STATEMENT_LIST
    0,    // PRINT_LIST
    0,    // EXPRESSION_LIST
    0,    // VARIABLE_LIST
    0,    // ARGUMENT_LIST
    0,    // PARAMETER_LIST
    0,    // DECLARATION_LIST
    0,    // FUNCTION
    0,    // STATEMENT
    0,    // BLOCK
    0,    // ASSIGNMENT_STATEMENT
    0,    // RETURN_STATEMENT
    0,    // PRINT_STATEMENT
    0,    // NULL_STATEMENT
    0,    // IF_STATEMENT
    0,    // WHILE_STATEMENT
    true, // EXPRESSION
    true, // RELATION
    0,    // DECLARATION
    0,    // PRINT_ITEM
    true, // IDENTIFIER_DATA
    0,    // NUMBER_DATA
    true, // STRING_DATA
    true, // FUNCTION_COMMENT
};

const bool node_malloc_data[LAST_NO_TYPE] = {
    0,    // PROGRAM
    0,    // GLOBAL_LIST
    0,    // GLOBAL
    0,    // STATEMENT_LIST
    0,    // PRINT_LIST
    0,    // EXPRESSION_LIST
    0,    // VARIABLE_LIST
    0,    // ARGUMENT_LIST
    0,    // PARAMETER_LIST
    0,    // DECLARATION_LIST
    0,    // FUNCTION
    0,    // STATEMENT
    0,    // BLOCK
    0,    // ASSIGNMENT_STATEMENT
    0,    // RETURN_STATEMENT
    0,    // PRINT_STATEMENT
    0,    // NULL_STATEMENT
    0,    // IF_STATEMENT
    0,    // WHILE_STATEMENT
    false, // EXPRESSION
    0,    // RELATION
    0,    // DECLARATION
    0,    // PRINT_ITEM
    true, // IDENTIFIER_DATA
    0,    // NUMBER_DATA
    true, // STRING_DATA
    true, // FUNCTION_COMMENT
};

const bool node_is_list[LAST_NO_TYPE] = {
    0,    // PROGRAM
    true, // GLOBAL_LIST
    0,    // GLOBAL
    true, // STATEMENT_LIST
    true, // PRINT_LIST
    true, // EXPRESSION_LIST
    true, // VARIABLE_LIST
    true, // ARGUMENT_LIST
    true, // PARAMETER_LIST
    true, // DECLARATION_LIST
    0,    // FUNCTION
    0,    // STATEMENT
    true, // BLOCK
    0,    // ASSIGNMENT_STATEMENT
    0,    // RETURN_STATEMENT
    true, // PRINT_STATEMENT
    0,    // NULL_STATEMENT
    0,    // IF_STATEMENT
    0,    // WHILE_STATEMENT
    0,    // EXPRESSION
    0,    // RELATION
    true,    // DECLARATION NOTE: This may need to change.
    0,    // PRINT_ITEM
    0,    // IDENTIFIER_DATA
    0,    // NUMBER_DATA
    0,    // STRING_DATA
    0,    // FUNCTION_COMMENT
};

const enum node_flag node_type_to_flag[N_NODE_FLAGS] = {
    FLAG_PROGRAM,               // PROGRAM
    FLAG_GLOBAL_LIST,           // GLOBAL_LIST
    FLAG_GLOBAL,                // GLOBAL
    FLAG_STATEMENT_LIST,        // STATEMENT_LIST
    FLAG_PRINT_LIST,            // PRINT_LIST
    FLAG_EXPRESSION_LIST,       // EXPRESSION_LIST
    FLAG_VARIABLE_LIST,         // VARIABLE_LIST
    FLAG_ARGUMENT_LIST,         // ARGUMENT_LIST
    FLAG_PARAMETER_LIST,        // PARAMETER_LIST
    FLAG_DECLARATION_LIST,      // DECLARATION_LIST
    FLAG_FUNCTION,              // FUNCTION
    FLAG_STATEMENT,             // STATEMENT
    FLAG_BLOCK,                 // BLOCK
    FLAG_ASSIGNMENT_STATEMENT,  // ASSIGNMENT_STATEMENT
    FLAG_RETURN_STATEMENT,      // RETURN_STATEMENT
    FLAG_PRINT_STATEMENT,       // PRINT_STATEMENT
    FLAG_NULL_STATEMENT,        // NULL_STATEMENT
    FLAG_IF_STATEMENT,          // IF_STATEMENT
    FLAG_WHILE_STATEMENT,       // WHILE_STATEMENT
    FLAG_EXPRESSION,            // EXPRESSION
    FLAG_RELATION,              // RELATION
    FLAG_DECLARATION,           // DECLARATION
    FLAG_PRINT_ITEM,            // PRINT_ITEM
    FLAG_IDENTIFIER_DATA,       // IDENTIFIER_DATA
    FLAG_NUMBER_DATA,           // NUMBER_DATA
    FLAG_STRING_DATA,           // STRING_DATA
    FLAG__UNUSED,
    FLAG_KEEP_CHILDREN_TYPE,      // FLAG: Keep the children type
};

const uint32_t node_list_parents[LAST_NO_TYPE] = {
    0x00,                                          // PROGRAM
    FLAG_PROGRAM           | FLAG_GLOBAL_LIST,     // GLOBAL_LIST
    FLAG_GLOBAL_LIST,                              // GLOBAL
    //FLAG_BLOCK             | FLAG_STATEMENT_LIST,  // STATEMENT_LIST
    FLAG_STATEMENT_LIST,  // STATEMENT_LIST
    FLAG_PRINT_STATEMENT   | FLAG_PRINT_LIST,      // PRINT_LIST

    /* This rule merges an EXPRESSION_LIST with an ARGUMENT_LIST whenever
     * the EXPRESSION_LIST is a direct descendant of an ARGUMENT_LIST node. */
    //FLAG_ARGUMENT_LIST     | FLAG_EXPRESSION_LIST, // EXPRESSION_LIST
    FLAG_KEEP_CHILDREN_TYPE | FLAG_ARGUMENT_LIST | FLAG_EXPRESSION_LIST,  // EXPRESSION_LIST (matches tree.correct files)

    /*
     * Merge VARIABLE_LIST with DECLARATION, DECLARATION_LIST, and VARIABLE_LIST,
     * but when there is a single node ((root) DECLARATION -> (child) VARIABLE_LIST),
     * then replace the DECLARATION node with the VARIABLE_LIST node.
     */
    //FLAG_KEEP_CHILDREN_TYPE | FLAG_DECLARATION | FLAG_DECLARATION_LIST  | FLAG_VARIABLE_LIST     | FLAG_PARAMETER_LIST,  // VARIABLE_LIST
    /* If this is not wanted, then replace the above with the following, and
     * see the comment later in this list. */
    FLAG_KEEP_CHILDREN_TYPE | FLAG_DECLARATION_LIST  | FLAG_VARIABLE_LIST     | FLAG_PARAMETER_LIST,  // VARIABLE_LIST (matches tree.correct files)

    0x00,                                          // ARGUMENT_LIST
    0x00,                                          // PARAMETER_LIST
    FLAG_DECLARATION_LIST,                         // DECLARATION_LIST
    0x00,                                          // FUNCTION
    FLAG_STATEMENT_LIST,                           // STATEMENT
    0x00,                                          // BLOCK
    FLAG_STATEMENT_LIST,                           // ASSIGNMENT_STATEMENT
    FLAG_STATEMENT_LIST,                           // RETURN_STATEMENT
    FLAG_STATEMENT_LIST,                           // PRINT_STATEMENT
    FLAG_STATEMENT_LIST,                           // NULL_STATEMENT
    FLAG_STATEMENT_LIST,                           // IF_STATEMENT
    FLAG_STATEMENT_LIST,                           // WHILE_STATEMENT
    0x00,                                          // EXPRESSION
    0x00,                                          // RELATION

    /* Merge DECLARATION with DECLARATION_LIST whenever possible. This will,
     * when used together with the above VARIABLE_LIST rule, ALWAYS result
     * in declarations being represented by a SINGLE VARIABLE_LIST.
     *
     * Since declarations are represented by a specific child (one of 2 children)
     * of a block, we know when a VARIABLE_LIST is a declaration by context.
     */
    //FLAG_DECLARATION_LIST,                         // DECLARATION
    0x00,                                          // DECLARATION (matches tree.correct files)
    FLAG_PRINT_LIST,                               // PRINT_ITEM
    0x00,                                          // IDENTIFIER_DATA
    0x00,                                          // NUMBER_DATA
    0x00,                                          // STRING_DATA
    0x00,                                          // FUNCTION_COMMENT
};

#undef AS_STR
