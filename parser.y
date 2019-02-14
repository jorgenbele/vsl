%{
#include "vslc.h"
#include "stdio.h"
#include "stdlib.h"
%}
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%right '~'

// Dangling ELSE:
// https://www.gnu.org/software/bison/manual/html_node/Non-Operators.html#Non-Operators
%right THEN ELSE

	//%expect 1
	//
%token FUNC PRINT RETURN CONTINUE IF THEN ELSE WHILE DO OPENBLOCK CLOSEBLOCK
%token VAR NUMBER IDENTIFIER STRING

%%

start: program

program           : global_list         { $$ = root = node_new(PROGRAM, NULL, 1, $1); } ;

global_list       : global              { $$ = node_new(GLOBAL_LIST, NULL, 1, $1);     }
        |       global_list global      { $$ = node_new(GLOBAL_LIST, NULL, 2, $1, $2); }
                ;

global            : function            { $$ = node_new(GLOBAL, NULL, 1, $1); }
        |       declaration             { $$ = node_new(GLOBAL, NULL, 1, $1); }
                ;


statement_list    : statement               { $$ = node_new(STATEMENT_LIST, NULL, 1, $1);     }
        |       statement_list statement    { $$ = node_new(STATEMENT_LIST, NULL, 2, $1, $2); }
                ;

print_list        : print_item             { $$ = node_new(PRINT_LIST, NULL, 1, $1);     }
        |       print_list ',' print_item  { $$ = node_new(PRINT_LIST, NULL, 2, $1, $3); }
                ;

expression_list   : expression                  { $$ = node_new(EXPRESSION_LIST, NULL, 1, $1);     }
        |       expression_list ',' expression  { $$ = node_new(EXPRESSION_LIST, NULL, 2, $1, $3); }
                ;

variable_list     : identifier                  { $$ = node_new(VARIABLE_LIST, NULL, 1, $1);     }
        |       variable_list  ',' identifier   { $$ = node_new(VARIABLE_LIST, NULL, 2, $1, $3); };

argument_list     : expression_list  { $$ = node_new(ARGUMENT_LIST, NULL, 1, $1); }
        | %empty
                ;

parameter_list    : variable_list  { $$ = node_new(PARAMETER_LIST, NULL, 1, $1); }
        | %empty
                ;

declaration_list  : declaration               { $$ = node_new(DECLARATION_LIST, NULL, 1, $1);     }
        |       declaration_list declaration  { $$ = node_new(DECLARATION_LIST, NULL, 2, $1, $2); }
                ;

function  : FUNC identifier  '(' parameter_list ')' statement  {  $$ = node_new(FUNCTION, NULL, 3, $2, $4, $6); };

statement :
                assignment_statement    { $$ = node_new(STATEMENT, NULL, 1, $1); }
        |       return_statement        { $$ = node_new(STATEMENT, NULL, 1, $1); }
        |       print_statement         { $$ = node_new(STATEMENT, NULL, 1, $1); }
        |       if_statement            { $$ = node_new(STATEMENT, NULL, 1, $1); }
        |       while_statement         { $$ = node_new(STATEMENT, NULL, 1, $1); }
        |       null_statement          { $$ = node_new(STATEMENT, NULL, 1, $1); }
        |       block                   { $$ = node_new(STATEMENT, NULL, 1, $1); }
                ;

block :
                OPENBLOCK declaration_list statement_list CLOSEBLOCK    { $$ = node_new(BLOCK, NULL, 2, $2, $3); }
        |       OPENBLOCK statement_list CLOSEBLOCK                     { $$ = node_new(BLOCK, NULL, 1, $2); }
                ;

assignment_statement : identifier ':' '=' expression   { $$ = node_new(ASSIGNMENT_STATEMENT, NULL, 2, $1, $4); } ;
return_statement     : RETURN expression               { $$ = node_new(RETURN_STATEMENT, NULL, 1, $2);         } ;
print_statement      : PRINT print_list                { $$ = node_new(PRINT_STATEMENT,  NULL, 1, $2);         } ;
null_statement       : CONTINUE                        { $$ = node_new(NULL_STATEMENT,   NULL, 0);             } ;

if_statement:
                IF relation THEN statement                 { $$ = node_new(IF_STATEMENT, NULL, 2, $2, $4);     }
        |       IF relation THEN statement ELSE statement  { $$ = node_new(IF_STATEMENT, NULL, 3, $2, $4, $6); }
                ;

while_statement: WHILE relation DO statement  { $$ = node_new(WHILE_STATEMENT, NULL, 2, $2, $4); } ;

relation:
                expression '=' expression   { $$ = node_new(RELATION, "=", 2, $1, $3); }
        |       expression '<' expression   { $$ = node_new(RELATION, "<", 2, $1, $3); }
        |       expression '>' expression   { $$ = node_new(RELATION, ">", 2, $1, $3); }
                ;

expression:
                expression '+' expression   { $$ = node_new(EXPRESSION,     "+",  2, $1, $3); }
        |       expression '-' expression   { $$ = node_new(EXPRESSION,     "-",  2, $1, $3); }
        |       expression '*' expression   { $$ = node_new(EXPRESSION,     "*",  2, $1, $3); }
        |       expression '/' expression   { $$ = node_new(EXPRESSION,     "/",  2, $1, $3); }
        |       '-' expression              { $$ = node_new(EXPRESSION,     "-",  1, $2    ); }
        |       '~' expression              { $$ = node_new(EXPRESSION,     "~",  1, $2    ); }
        |       '(' expression ')'          { $$ = $2; }
        |       number                      { $$ = node_new(EXPRESSION,    NULL,  1, $1    ); }
        |       identifier                  { $$ = node_new(EXPRESSION,    NULL,  1, $1    ); }
        |       identifier '(' argument_list ')' { $$ = node_new(EXPRESSION,  NULL,  2, $1, $3); }
                ;

declaration:
         VAR variable_list { $$ = node_new(DECLARATION, NULL, 1, $2); }
                ;

print_item:     expression  { $$ = node_new(PRINT_ITEM, NULL, 1, $1); }
        |       string      { $$ = node_new(PRINT_ITEM, NULL, 1, $1); }
                ;

identifier:     IDENTIFIER          { $$ = node_new(IDENTIFIER_DATA, $1, 0); } ;
number    :     NUMBER              { $$ = node_new(NUMBER_DATA, $1, 0);     } ;
string    :     STRING              { $$ = node_new(STRING_DATA, $1, 0);     } ;

%%

int yyerror(const char *error)
{
    fprintf(stderr, "%s on line %d\n", error, yylineno);
    exit(EXIT_FAILURE);
}
