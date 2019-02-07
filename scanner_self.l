%{
%}
%option noyywrap
%option array
%option yylineno

%%
[\t\n\r\v ]*       {                   } /* whitespace is ignored */
\"[^\n\"]*\"             { printf("%s: %s\n", "STRING"       , yytext);}
[0-9]+                 { printf("%s: %s\n", "NUMBER"         , yytext);}
\/\/.*                 { printf("%s: %s\n", "COMMENT"        , yytext);} /* comments are ignored */
"def"                  { printf("%s\n",     "FUNC"           ); }
"begin"                { printf("%s\n",     "OPENBLOCK"      ); }
"end"                  { printf("%s\n",     "CLOSEBLOCK"     ); }
"return"               { printf("%s\n",     "RETURN"         ); }
"print"                { printf("%s\n",     "PRINT"          ); }
"if"                   { printf("%s\n",     "IF"             ); }
"then"                 { printf("%s\n",     "THEN"           ); }
"else"                 { printf("%s\n",     "ELSE"           ); }
"while"                { printf("%s\n",     "WHILE"          ); }
"do"                   { printf("%s\n",     "DO"             ); }
"var"                  { printf("%s\n",     "VAR"            ); }
[a-zA-Z_][0-9a-zA-Z_]* { printf("%s: %s\n", "IDENTIFIER"     , yytext);}

"+"                    { printf("%s\n",     "PLUS"           ); }
"-"                    { printf("%s\n",     "MINUS"          ); }
"/"                    { printf("%s\n",     "DIVISION"       ); }
"*"                    { printf("%s\n",     "MULTIPLICATION" ); }
":="                   { printf("%s\n",     "ASSIGNMENT"     ); }
"="                    { printf("%s\n",     "EQUAL"          ); }
"<"                    { printf("%s\n",     "LESS_THAN"      ); }
">"                    { printf("%s\n",     "GREATER_THAN"   ); }
.                      { printf("%c\n", yytext[0]);             }
%%
