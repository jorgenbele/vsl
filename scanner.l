
%{
#include "vslc.h"
%}
%option noyywrap
%option array
%option yylineno

%%
[\t\n\r\v ]*           {} /* whitespace is ignored */
\;[^\n\;]*\;           { return STRING;       }
[0-9]+                 { return NUMBER;       }
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
[a-zA-Z_][0-9a-zA-Z_]* { return IDENTIFIER;   }
.                      { return yytext[0];    }
%%
