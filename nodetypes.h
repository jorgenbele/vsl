#ifndef __NODETYPES_H_
#define __NODETYPES_H_

#include <stdbool.h>

enum node_type {
    PROGRAM,
    GLOBAL_LIST,
    GLOBAL,
    STATEMENT_LIST,
    PRINT_LIST,
    EXPRESSION_LIST,
    VARIABLE_LIST,
    ARGUMENT_LIST,
    PARAMETER_LIST,
    DECLARATION_LIST,
    FUNCTION,
    STATEMENT,
    BLOCK,
    ASSIGNMENT_STATEMENT,
    RETURN_STATEMENT,
    PRINT_STATEMENT,
    NULL_STATEMENT,
    IF_STATEMENT,
    WHILE_STATEMENT,
    EXPRESSION,
    RELATION,
    DECLARATION,
    PRINT_ITEM,
    IDENTIFIER_DATA,
    NUMBER_DATA,
    STRING_DATA
};

extern const char *node_t2s[26];     // node type to type string
extern const bool node_tpr_data[26]; // node type has printable data, lookup table

#endif // __NODETYPES_H_
