#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

#include <time.h>

#include "nodetypes.h"

int main(int argc, char *argv[]) {
    (void) argc; (void) argv;

    struct timespec t;
    memset(&t, 0, sizeof(t));

    for (int i = 0; i < LAST_NO_TYPE; i++) {
        node_type_to_string[i];
    }

    return 0;
}
