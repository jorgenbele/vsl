#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_IMPLEMENTED(name, message)                  \
    do {                                                \
        fprintf(stderr,                                 \
                "%s:%d - %s is not implemented, %s\n",  \
                __FILE__, __LINE__, #name, (message)); \
    } while (0)

#ifdef DEBUG
#define DEBUG_START_TIME_TAKING_BLOCK(name)                     \
        struct timespec start_##name;                           \
        assert(!clock_gettime(CLOCK_MONOTONIC, &start_##name))

#define DEBUG_END_TIME_TAKING_BLOCK(name)                                       \
        struct timespec end_##name;                                             \
        assert(!clock_gettime(CLOCK_MONOTONIC, &end_##name));                   \
        {                                                                       \
            const int64_t diff_s = end_##name.tv_sec - start_##name.tv_sec;     \
            const int64_t diff_ns = end_##name.tv_nsec - start_##name.tv_nsec;  \
            const int64_t diff_ms = diff_ns/1000000;                            \
            fprintf(stderr, #name ": Executed in %ld s %ld ns (%ld ms)\n",      \
                    diff_s, diff_ns, diff_ms);                                  \
        }                                                                       \

#define DEBUG_END_TIME_TAKING_BLOCK_FMT(name, fmt, ...)                         \
        struct timespec end_##name;                                             \
        assert(!clock_gettime(CLOCK_MONOTONIC, &end_##name));                   \
        {                                                                       \
            const int64_t diff_s = end_##name.tv_sec - start_##name.tv_sec;     \
            const int64_t diff_ns = end_##name.tv_nsec - start_##name.tv_nsec;  \
            const int64_t diff_ms = diff_ns/1000000;                            \
            fprintf(stderr, fmt ": Executed in %ld s %ld ns (%ld ms)\n",        \
                    __VA_ARGS__, diff_s, diff_ns, diff_ms);                     \
        }                                                                       \
    }

#else

#define DEBUG_START_TIME_TAKING_BLOCK(name)
#define DEBUG_END_TIME_TAKING_BLOCK(name)
#define DEBUG_END_TIME_TAKING_BLOCK_FMT(name, fmt, ...)

#endif

#define MIN(x, y) ((x) < (y) ? (x) : (y))


void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
void *xrealloc(void *ptr, size_t size);
void debug(const char *fmt, ...);

#endif /* __UTILS_H_ */
