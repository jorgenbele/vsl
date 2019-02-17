
%{
#include "vslc.h"

#define SAVE_STR yylval.str = strdup(yytext)
#define SAVE_INT sscanf(yytext, "%" SCNdit, &yylval.integer)
%}
%option noyywrap
%option array
%option yylineno

%%
[\t\n\r\v ]*           {} /* whitespace is ignored */
\"([^\n\"]|\\\")*\"    { SAVE_STR; return STRING; } /* accepts \x where x is a double quote */
[0-9]+                 { SAVE_INT; return NUMBER; }

\/\/.*                 {} /* comments are ignored */
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
[a-zA-Z_][0-9a-zA-Z_]* { SAVE_STR; return IDENTIFIER; }
.                      { return yytext[0];    }
%%
