%{
#include "vslc.h"
#include "stdio.h"
#include "stdlib.h"
%}
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%right '~'
	//%expect 1
	//
%token FUNC PRINT RETURN CONTINUE IF THEN ELSE WHILE DO OPENBLOCK CLOSEBLOCK
%token VAR NUMBER IDENTIFIER STRING

%%

program           : global_list { root = node_new(PROGRAM, NULL, 0); }  ;
global_list       : global          | global_list global                ;
global            : function        | declaration                       ;
statement_list    : statement       | statement_list statement          ;
print_list        : print_item      | print_list      ',' print_item    ;
expression_list   : expression      | expression_list ',' expression    ;
variable_list     : identifier      | variable_list   ',' identifier    ;
argument_list     : expression_list | %empty                            ;
parameter_list    : variable_list   | %empty                            ;
declaration_list  : declaration     | declaration_list declaration      ;

function  : FUNC identifier  '(' parameter_list ')' statement    ;
statement :
                assignment_statement
        |       return_statement
        |       print_statement
        |       if_statement
        |       while_statement
        |       null_statement
        |       block
    ;

block :
                OPENBLOCK declaration_list statement_list CLOSEBLOCK
        |       OPENBLOCK statement_list CLOSEBLOCK
    ;

assignment_statement : identifier ':' '=' expression ;
return_statement     : RETURN expression             ;
print_statement      : PRINT print_list              ;
null_statement       : CONTINUE                      ;

if_statement:
                IF relation THEN statement
        |       IF relation THEN statement ELSE statement
    ;

while_statement:
                WHILE relation DO statement
        ;

relation:
                expression '=' expression
        |       expression '<' expression
        |       expression '>' expression
        ;

expression:
                expression '+' expression
        |       expression '-' expression
        |       expression '*' expression
        |       expression '/' expression
        |       '-' expression
        |       '~' expression
        |       '(' expression ')'
        |       number | identifier | identifier '(' argument_list ')'
        ;

declaration:
         VAR variable_list
        ;

print_item:     expression | string ;
identifier:     IDENTIFIER          ;
number    :     NUMBER              ;
string    :     STRING              ;

%%

int yyerror(const char *error)
{
    fprintf(stderr, "%s on line %d\n", error, yylineno);
    exit(EXIT_FAILURE);
}
