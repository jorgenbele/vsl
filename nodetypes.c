#include "node.h"
#include "nodetypes.h"

#define AS_STR(x) #x

const char *node_t2s[26] = {
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
    AS_STR(STRING_DATA)
};

const bool node_tpr_data[26] = {
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
    true, // DECLARATION
    0,    // PRINT_ITEM
    true, // IDENTIFIER_DATA
    0,    // NUMBER_DATA
    true, // STRING_DATA
};

const bool node_malloc_data[26] = {
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
    true,    // DECLARATION
    0,    // PRINT_ITEM
    true, // IDENTIFIER_DATA
    0,    // NUMBER_DATA
    true, // STRING_DATA
};

#undef AS_STR
