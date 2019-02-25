#ifndef __VSLC_H_
#define __VSLC_H_

/* #define DEBUG_VEC */

#include "nodetypes.h"
#include "node.h"
#include "tree.h"
#include "utils.h"
#include "y.tab.h"

int yyerror (const char *error);
int yylex_destroy(void);

extern int yylineno;
extern int yycolumn;
extern YYLTYPE yylloc;

extern int yylex (void);
extern char yytext[];

extern node_t *root;


#endif // __VSLC_H_
