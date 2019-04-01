#ifndef __NODE_SRC_H_
#define __NODE_SRC_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "node.h"
#include "nodetypes.h"

/* node_print_source():
 *  Recreates a source code representation of the ast root.
 *  NOTE: The recreated source code will not contain comments, since
 *      the comments are not stored in the ast (and making it so is a
 *      pain I will not endure.).
 */
void node_print_source(node_t *root);
void node_print_statement(node_t *n);
void node_print_expression(node_t *n);

#define SRC_NEVER_NEWLINE 0x2
#define SRC_ALWAYS_NEWLINE 0x1

/* Can be set to override the default: 1. */
extern FILE *src_print_file;
extern char *src_line_prefix;
extern int src_newline;
extern int src_print_line;

#endif /* __NODE_SRC_H_ */
