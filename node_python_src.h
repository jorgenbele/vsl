#ifndef __NODE_PYTHON_SRC_H_
#define __NODE_PYTHON_SRC_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "node.h"
#include "nodetypes.h"

void transpile_to_python(node_t *n);

/* Can be set to override the default: 1. */
extern int python_src_print_fileno;

#endif // __NODE_PYTHON_SRC_H_
