%{
#include "vslc.h"
#include "stdio.h"
#include "stdlib.h"

#define C0(type, data) \
         (node_new_lc((type), (data), (yylineno), (yycolumn), 0))

#define C1(type, data, a1) \
         (node_new_lc((type), (data), (yylineno), (yycolumn), 1, (a1)))

#define C2(type, data, a1, a2) \
         (node_new_lc((type), (data), (yylineno), (yycolumn), 2, (a1), (a2)))

#define C3(type, data, a1, a2, a3) \
         (node_new_lc((type), (data), (yylineno), (yycolumn), 3, (a1), (a2), (a3)))

%}
%locations

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%right '~'

// Dangling ELSE:
// https://www.gnu.org/software/bison/manual/html_node/Non-Operators.html#Non-Operators
%right THEN ELSE

%union {
    node_t *node;
    char *str;            /* Will always be a malloc'ed string. */
    enum node_type type;
    int_type integer;
};

//%expect 1

/* Terminals types */
%token  <type>     FUNC PRINT RETURN CONTINUE IF THEN ELSE WHILE DO OPENBLOCK CLOSEBLOCK VAR
%token  <str>      IDENTIFIER STRING
%token  <integer>  NUMBER

%token  <str>      FUNCTION_COMMENT_PARSER

/* Non-terminals types */
%type   <node> program global_list global function declaration_list declaration statement_list statement
%type   <node> print_list print_item
%type   <node> expression_list expression
%type   <node> variable_list argument_list parameter_list
%type   <node> assignment_statement return_statement print_statement if_statement while_statement null_statement
%type   <node> block relation
%type   <node> identifier number string

%type   <node> function_comment

%%

start: program

program:     global_list                        { $$ = root = C1(PROGRAM, NULL, $1); }
        ;

global_list: global                             { $$ = C1(GLOBAL_LIST, NULL, $1);     }
        |    global_list global                 { $$ = C2(GLOBAL_LIST, NULL, $1, $2); }
        ;

global:      function                           { $$ = C1(GLOBAL, NULL, $1); }
        |    declaration                        { $$ = C1(GLOBAL, NULL, $1); }
        ;

statement_list:
             statement                          { $$ = C1(STATEMENT_LIST, NULL, $1);     }
        |    statement_list statement           { $$ = C2(STATEMENT_LIST, NULL, $1, $2); }
        ;

print_list:  print_item                         { $$ = C1(PRINT_LIST, NULL, $1);     }
        |    print_list ',' print_item          { $$ = C2(PRINT_LIST, NULL, $1, $3); }
        ;

expression_list:
             expression                         { $$ = C1(EXPRESSION_LIST, NULL, $1);     }
        |    expression_list ',' expression     { $$ = C2(EXPRESSION_LIST, NULL, $1, $3); }
        ;

variable_list:
             identifier                         { $$ = C1(VARIABLE_LIST, NULL, $1);     }
        |    variable_list ',' identifier       { $$ = C2(VARIABLE_LIST, NULL, $1, $3); }
        ;

/* NOTE: I create empty ARGUMENT_LIST and PARAMETER_LIST nodes to avoid NULL
 * checks (and warnings), this will result in the '*.tree' and '*.tree.correct'
 * files to differ since PARAMETER_LIST is printed instead of (nil). */
argument_list:  expression_list  { $$ = C1(ARGUMENT_LIST,  NULL, $1); } | %empty { $$ = C0(ARGUMENT_LIST, NULL);  };
parameter_list: variable_list    { $$ = C1(PARAMETER_LIST, NULL, $1); } | %empty { $$ = C0(PARAMETER_LIST, NULL); };

declaration_list: declaration                   { $$ = C1(DECLARATION_LIST, NULL, $1);     }
        |       declaration_list declaration    { $$ = C2(DECLARATION_LIST, NULL, $1, $2); }
        ;

function: function_comment function {
              $2->comment = $1;
              $$ = $2;
             }
            | FUNC identifier  '(' parameter_list ')' statement  { $$ = C3(FUNCTION, NULL, $2, $4, $6); };

function_comment: FUNCTION_COMMENT_PARSER { $$ = C0(FUNCTION_COMMENT, $1); } ;

statement:
             assignment_statement    { $$ = C1(STATEMENT, NULL, $1); }
        |    return_statement        { $$ = C1(STATEMENT, NULL, $1); }
        |    print_statement         { $$ = C1(STATEMENT, NULL, $1); }
        |    if_statement            { $$ = C1(STATEMENT, NULL, $1); }
        |    while_statement         { $$ = C1(STATEMENT, NULL, $1); }
        |    null_statement          { $$ = C1(STATEMENT, NULL, $1); }
        |    block                   { $$ = C1(STATEMENT, NULL, $1); }
        ;

block:
             OPENBLOCK declaration_list statement_list CLOSEBLOCK    { $$ = C2(BLOCK, NULL, $2, $3); }
        |    OPENBLOCK statement_list CLOSEBLOCK                     { $$ = C1(BLOCK, NULL, $2);     }
        ;

assignment_statement: identifier ':' '=' expression   { $$ = C2(ASSIGNMENT_STATEMENT, NULL, $1, $4); } ;
return_statement:     RETURN expression               { $$ = C1(RETURN_STATEMENT, NULL, $2);         } ;
print_statement:      PRINT print_list                { $$ = C1(PRINT_STATEMENT,  NULL, $2);         } ;
null_statement:       CONTINUE                        { $$ = C0(NULL_STATEMENT,   NULL);             } ;

if_statement:
             IF relation THEN statement                 { $$ = C2(IF_STATEMENT, NULL, $2, $4);     }
        |    IF relation THEN statement ELSE statement  { $$ = C3(IF_STATEMENT, NULL, $2, $4, $6); }
        ;

while_statement: WHILE relation DO statement  { $$ = C2(WHILE_STATEMENT, NULL, $2, $4); } ;

/* NOTE: A table mapping the node_t types to whether it was
 *       allocated or not can be found in nodetypes.c. This
 *       is why I pass (const char *) like "=" as data. */
relation:
             expression '=' expression { $$ = C2(RELATION, "=", $1, $3); }
        |    expression '<' expression { $$ = C2(RELATION, "<", $1, $3); }
        |    expression '>' expression { $$ = C2(RELATION, ">", $1, $3); }
        ;

expression:
             expression '+' expression        { $$ = C2(EXPRESSION, "+", $1, $3); }
        |    expression '-' expression        { $$ = C2(EXPRESSION, "-", $1, $3); }
        |    expression '*' expression        { $$ = C2(EXPRESSION, "*", $1, $3); }
        |    expression '/' expression        { $$ = C2(EXPRESSION, "/", $1, $3); }

                /* Unary operations. Since '-' has other uses
                 * %prec UMINUS is used to apply 'noassoc'. */
        |    '-' expression %prec UMINUS      { $$ = C1(EXPRESSION, "-", $2);     }
        |    '~' expression                   { $$ = C1(EXPRESSION, "~", $2);     }
        |    '(' expression ')'               { $$ = $2; }
        //|    '(' expression ')'               { $$ = C1(EXPRESSION, "(expr)", $2); }

        |    number                           { $$ = C1(EXPRESSION, NULL, $1);     }
        |    identifier                       { $$ = C1(EXPRESSION, NULL, $1);     }

            /* NOTE: "func_call" instead of NULL */
        |    identifier '(' argument_list ')' { $$ = C2(EXPRESSION, "func_call", $1, $3); }
        ;

declaration: VAR variable_list { $$ = C1(DECLARATION, NULL, $2); } ;

print_item:
             expression  { $$ = C1(PRINT_ITEM, NULL, $1); }
        |    string      { $$ = C1(PRINT_ITEM, NULL, $1); }
        ;

identifier:  IDENTIFIER  { $$ = C0(IDENTIFIER_DATA, NODE_DATA_CAST $<str>1);     } ;
number:      NUMBER      { $$ = C0(NUMBER_DATA,     NODE_DATA_CAST $<integer>1); } ;
string:      STRING      { $$ = C0(STRING_DATA,     NODE_DATA_CAST $<str>1);     } ;

%%

int yyerror(const char *error)
{
    fprintf(stderr, "%s on line %d, col:%d\n", error, yylineno, yycolumn);
    exit(EXIT_FAILURE);
}
