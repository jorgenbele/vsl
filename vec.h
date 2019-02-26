/*
 * File: vec.h
 * Author: Jørgen Bele Reinfjell
 * Date: xx.08.2018 [dd.mm.yyyy]
 */

#ifndef __VEC_H_
#define __VEC_H_

#ifdef DEBUG_VEC
#include <assert.h>
#endif

#include <stdlib.h>
#include <memory.h>

enum {ERR_VEC_EMPTY=1,ERR_VEC_TOO_SHORT,ERR_VEC_INIT};

#define VEC_DEFAULT(type) \
    __vec_default_##type

#define DEF_VEC_STRUCT(name, type)              \
    struct vec_##name                           \
    {                                           \
        size_t size;                            \
        size_t len;                             \
        int error;                              \
        size_t allocs;                          \
        type *data;                             \
    };                                          \
    typedef struct vec_##name vec_##name;

#define DEF_VEC_INIT(name, type)                \
    int vec_init_##name(struct vec_##name *v)   \
    {                                           \
        memset(v, 0, sizeof(*v));               \
        return 0;                               \
    }

#define DEF_VEC_INIT_W(name, type)                      \
    int vec_init_w_##name(struct vec_##name *v,         \
                          const type tv[], size_t ts)   \
    {                                                   \
        memset(v, 0, sizeof(*v));                       \
        v->size = ts;                                   \
        v->len = ts;                                    \
        v->allocs = 1;                                  \
        v->data = malloc(sizeof(*tv) * ts);             \
        if (!v->data) { return 1; }                     \
        memcpy(v->data, tv, sizeof(*tv) * ts);          \
        return 0;                                       \
    }

#define DEF_VEC_DESTROY(name, type)                 \
    int vec_destroy_##name(struct vec_##name *v)    \
    {                                               \
        free(v->data);                              \
        return 0;                                   \
    }

#define VEC_EXTEND(type)                                    \
    if (v->size < size) {                                   \
        if (size && size >= v->size<<1) {                   \
            v->size = size;                                 \
        } else {                                            \
            v->size = v->size ? v->size<<1 : 2;             \
        }                                                   \
        v->data = realloc(v->data, v->size*sizeof(type));   \
        v->allocs++;                                        \
    }                                                       \

#define DEF_VEC_EXTEND(name, type)                              \
    int vec_extend_##name(struct vec_##name *v, size_t size)    \
    {                                                           \
        VEC_EXTEND(type);                                       \
        return !v->data;                                        \
    }

#define DEF_VEC_PUSH(name, type)                        \
    int vec_push_##name(struct vec_##name *v, type t)   \
    {                                                   \
        if (v->len + 1 >= v->size) {                    \
            size_t size = v->len + 1;                   \
            VEC_EXTEND(type);                           \
            if (!v->data) { return 1; }                 \
        }                                               \
        v->data[v->len] = t;                            \
        v->len++;                                       \
        return 0;                                       \
    }

#define DEF_VEC_POP(name, type, def)            \
    type vec_pop_##name(struct vec_##name *v)   \
    {                                           \
        if (!v->len) {                          \
            v->error = ERR_VEC_EMPTY;           \
            return def;                         \
        }                                       \
        v->len--;                               \
        return v->data[v->len];                 \
    }

#define DEF_VEC_PEEK(name, type, def)           \
    type vec_peek_##name(struct vec_##name *v)  \
    {                                           \
        if (!v->len) {                          \
            v->error = ERR_VEC_EMPTY;           \
            return def;                         \
        }                                       \
        return v->data[v->len-1];               \
    }

#define DEF_VEC_PEEK_PTR(name, type, def)           \
    type *vec_peek_ptr_##name(struct vec_##name *v) \
    {                                               \
        if (!v->len) {                              \
            v->error = ERR_VEC_EMPTY;               \
            return NULL;                            \
        }                                           \
        return &v->data[v->len-1];                  \
    }

#define DEF_VEC_SET(name, type, def)                            \
    int vec_set_##name(struct vec_##name *v, type t, size_t i)  \
    {                                                           \
        if (i + 1 > v->len) {                                   \
            v->error = ERR_VEC_EMPTY;                           \
            return 1;                                           \
        }                                                       \
        v->data[i] = t;                                         \
        return 0;                                               \
    }

#define DEF_VEC_GET(name, type, def)                    \
    type vec_get_##name(struct vec_##name *v, size_t i) \
    {                                                   \
        if (i + 1 > v->len) {                           \
            v->error = ERR_VEC_EMPTY;                   \
            return def;                                 \
        }                                               \
        return v->data[i];                              \
    }

#define DEF_VEC_GET_PTR(name, type, def)                        \
    type *vec_get_ptr_##name(struct vec_##name *v, size_t i)    \
    {                                                           \
        if (i + 1 > v->len) {                                   \
            v->error = ERR_VEC_EMPTY;                           \
            return NULL;                                        \
        }                                                       \
        return &v->data[i];                                     \
    }

#define DEF_VEC_AFTER(name, type, def)                          \
    struct vec_##name vec_after_##name(struct vec_##name *v,    \
                                       size_t i)                \
    {                                                           \
        struct vec_##name vec;                                  \
        if (v->len < i) {                                       \
            vec_init_##name(&vec);                              \
            return vec;                                         \
        }                                                       \
        if (vec_init_w_##name(&vec, &v->data[i], v->len-i)) {   \
            v->error = ERR_VEC_INIT;                            \
        }                                                       \
        return vec;                                             \
    }


#define DEF_VEC_PROTOTYPES(name, type)                              \
    int vec_init_##name(struct vec_##name *v);                      \
    int vec_init_w_##name(struct vec_##name *v,                     \
                          const type tv[], size_t ts);              \
    int vec_destroy_##name(struct vec_##name *v);                   \
    int vec_extend_##name(struct vec_##name *v, size_t size);       \
    int vec_push_##name(struct vec_##name *v, type t);              \
    type vec_pop_##name(struct vec_##name *v);                      \
    type vec_peek_##name(struct vec_##name *v);                     \
    type *vec_peek_ptr_##name(struct vec_##name *v);                \
    int vec_set_##name(struct vec_##name *v, type t, size_t i);     \
    type vec_get_##name(struct vec_##name *v, size_t i);            \
    type *vec_get_ptr_##name(struct vec_##name *v, size_t i);       \
    struct vec_##name vec_after_##name(struct vec_##name *v, size_t i)


#define DEF_VEC_HEADER(name, type)              \
    DEF_VEC_STRUCT(name, type)                  \
        DEF_VEC_PROTOTYPES(name, type)

#define DEF_VEC_FUNCS(name, type, def)          \
    DEF_VEC_INIT(name, type)                    \
        DEF_VEC_INIT_W(name, type)              \
        DEF_VEC_DESTROY(name, type)             \
        DEF_VEC_EXTEND(name, type)              \
        DEF_VEC_PUSH(name, type)                \
        DEF_VEC_POP(name, type, def)            \
        DEF_VEC_PEEK(name, type, def)           \
        DEF_VEC_PEEK_PTR(name, type, def)       \
        DEF_VEC_SET(name, type, def)            \
        DEF_VEC_GET(name, type, def)            \
        DEF_VEC_GET_PTR(name, type, def)        \
        DEF_VEC_AFTER(name, type, def)

#define DEF_VEC(name, type, def)                \
    DEF_VEC_HEADER(name, type);                 \
        DEF_VEC_FUNCS(name, type, def)

/*
 * Macro usage definitions
 */

#define VEC(type) vec_##type

#ifndef DEBUG_VEC

    #define VEC_INIT(vec, type) \
        vec_init_##type((vec))

    #define VEC_INIT_W(vec, type, array, size) \
        vec_init_w_##type((vec), (array), (size))

    #define VEC_DESTROY(vec, type) \
        vec_destroy_##type((vec))

    #define VEC_PUSH(vec, type, elem) \
        vec_push_##type((vec), (elem))

    #define VEC_PEEK_PTR(vec, type, elem) \
        vec_peek_ptr_##type((vec), (elem))

    #define VEC_PEEK(vec, type) \
        vec_peek_##type((vec))

    #define VEC_POP(vec, type) \
        vec_pop_##type((vec))

    #define VEC_GET(vec, type, i) \
        vec_get_##type((vec), (i))

    #define VEC_GET_PTR(vec, type, i) \
        vec_get_ptr_##type((vec), (i))

    #define VEC_LEN(vec) ((vec)->len)

    #define VEC_ARRAY_PTR(vec) ((vec)->data)

    #define VEC_ERROR(vec) ((vec)->error)

#else
    #warning "Debugging of vector enabled"
    #define VEC_INIT(vec, type) \
        vec_init_##type((vec)), assert(!(vec)->error)

    #define VEC_INIT_W(vec, type, array, size) \
        vec_init_w_##type((vec), (array), (size)), assert(!(vec)->error)

    #define VEC_DESTROY(vec, type) \
        vec_destroy_##type((vec)), assert(!(vec)->error)

    #define VEC_PUSH(vec, type, elem) \
        vec_push_##type((vec), (elem)), assert(!(vec)->error)

    #define VEC_PEEK_PTR(vec, type, elem) \
        vec_peek_ptr_##type((vec), (elem))

    #define VEC_PEEK(vec, type) \
        vec_peek_##type((vec)), assert(!(vec)->error)

    #define VEC_POP(vec, type) \
        vec_pop_##type((vec)), assert(!(vec)->error)

    #define VEC_GET(vec, type, i) \
        vec_get_##type((vec), (i))

    #define VEC_GET_PTR(vec, type, i) \
        vec_get_ptr_##type((vec), (i))

    #define VEC_LEN(vec) ((vec)->len)

    #define VEC_ARRAY_PTR(vec) ((vec)->data)

    #define VEC_ERROR(vec) ((vec)->error)

#endif /* DEBUG_VEC */


#endif /* __VEC_H_ */
