#include "utils.h"

#include <assert.h>

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    assert(ptr);
    return ptr;
}

void *xcalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);
    assert(ptr);
    return ptr;
}


void *xrealloc(void *ptr, size_t size)
{
    void *n_ptr = realloc(ptr, size);
    assert(n_ptr);
    return n_ptr;
}
