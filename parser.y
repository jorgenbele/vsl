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

%token FUNC PRINT RETURN CONTINUE IF THEN ELSE WHILE DO OPENBLOCK CLOSEBLOCK
%token VAR NUMBER IDENTIFIER STRING

%%
program :
      FUNC {
        root = malloc(sizeof(node_t));
        node_init(root, PROGRAM, NULL, 0);
      }
    ;
%%

int yyerror(const char *error)
{
    fprintf(stderr, "%s on line %d\n", error, yylineno);
    exit(EXIT_FAILURE);
}
