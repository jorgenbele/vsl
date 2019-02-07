#ifndef __VSLC_H_
#define __VSLC_H_

#include "nodetypes.h"
#include "node.h"
#include "tree.h"
#include "utils.h"
#include "y.tab.h"

int yyerror (const char *error);
extern int yylineno;
extern int yylex (void);
extern char yytext[];

extern node_t *root;

#endif // __VSLC_H_
