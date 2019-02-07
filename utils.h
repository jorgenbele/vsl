#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdio.h>
#include <stdlib.h>

#define NOT_IMPLEMENTED(name, message)                  \
    do {                                                \
        fprintf(stderr,                                 \
                "%s:%d - %s is not implemented, %s\n",  \
                __FILE__, __LINE__, (name), (message)); \
    } while (0)

void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
void *xrealloc(void *ptr, size_t size);

#endif // __UTILS_H_
