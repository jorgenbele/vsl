
%{
#include "vslc.h"

#define SAVE_STR yylval.str = strdup(yytext)
#define SAVE_INT sscanf(yytext, "%" SCNdit, &yylval.integer)


int yycolumn = 0;

/* This is executed before every action. */
/* Taken from: https://stackoverflow.com/questions/26854374/how-do-i-use-yy-bs-lineno-and-yy-bs-column-in-flex */
#define YY_USER_ACTION                                                   \
    start_line = prev_yylineno; start_column = yycolumn;                \
    if (yylineno == prev_yylineno) yycolumn += yyleng;                  \
    else {                                                              \
        for (yycolumn = 1; yytext[yyleng - yycolumn] != '\n'; ++yycolumn) {} \
        yycolumn--;                                                     \
        prev_yylineno = yylineno;                                       \
  }


%}
%option noyywrap
%option array
%option yylineno

%%
   int start_line, start_column;
   int prev_yylineno = yylineno;

[\t\n\r\v ]*           {} /* whitespace is ignored */
\"([^\n\"]|\\\")*\"    { SAVE_STR; return STRING; } /* accepts \x where x is a double quote */
[0-9]+                 { SAVE_INT; return NUMBER; }

\/\/.*                 {} /* comments are ignored */

\"\"\"[^\"\"\"]*\"\"\" { SAVE_STR; return FUNCTION_COMMENT_PARSER; } /* comments are ignored */

"def"                  { return FUNC;         }
"begin"                { return OPENBLOCK;    }
"end"                  { return CLOSEBLOCK;   }
"return"               { return RETURN;       }
"print"                { return PRINT;        }
"if"                   { return IF;           }
"then"                 { return THEN;         }
"else"                 { return ELSE;         }
"while"                { return WHILE;        }
"do"                   { return DO;           }
"var"                  { return VAR;          }
"continue"             { return CONTINUE;     } /* NOT SPECIFIED IN LIST!! */

"asm"[^\n]*           { SAVE_STR; return ASM; }

[a-zA-Z_][0-9a-zA-Z_]* { SAVE_STR; return IDENTIFIER; }
.                      { return yytext[0];    }
%%
