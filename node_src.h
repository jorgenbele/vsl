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

/* Can be set to override the default: 1. */
extern int src_print_fileno;

#endif /* __NODE_SRC_H_ */
