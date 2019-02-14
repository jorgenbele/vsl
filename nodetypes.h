#ifndef __NODETYPES_H_
#define __NODETYPES_H_

#include <stdbool.h>

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
    LAST_NO_TYPE         = 26
};

extern const char *node_t2s[LAST_NO_TYPE];        // node type to type string
extern const bool node_tpr_data[LAST_NO_TYPE];    // node type has printable data, lookup table
extern const bool node_malloc_data[LAST_NO_TYPE]; // node type has malloc'ed data, lookup table

#endif // __NODETYPES_H_
