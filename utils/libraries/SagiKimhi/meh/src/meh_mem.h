#ifndef MEH_MEMORY_MACROS_H_
#define MEH_MEMORY_MACROS_H_

#ifndef meh_free
#define meh_free(...) free(__VA_ARGS__)
#endif

#ifndef meh_alloc
#define meh_alloc malloc
#endif

#ifndef meh_calloc
#define meh_calloc calloc
#endif

#ifndef meh_realloc
#define meh_realloc realloc
#endif

#endif
