#ifndef MEH_DARRAY_H_
#define MEH_DARRAY_H_

#include <sys/types.h>

/* -----------------------------------------------------------------------------
 * Macros
 * ----------------------------------------------------------------------------- */

#ifndef meh_da_print
# define meh_da_print(da) meh_darray_print(da, #da)
#endif

/* -----------------------------------------------------------------------------
 * Structs
 * ----------------------------------------------------------------------------- */

struct meh_darray {
    size_t size;
    size_t stride;
    size_t capacity;
    void *items;
};

/* -----------------------------------------------------------------------------
 * Methods
 * ----------------------------------------------------------------------------- */

#ifndef meh_darray_create
# define meh_darray_create(T) meh_darray_create_(sizeof(T))
#endif

extern struct meh_darray
meh_darray_create_(size_t item_sz);

extern void
meh_darray_destroy(struct meh_darray *da);

extern void *
meh_darray_get(struct meh_darray da, size_t index);

extern int
meh_darray_set(struct meh_darray da, size_t index, const void *item);

extern void *
meh_darray_pop(struct meh_darray *da);

extern void *
meh_darray_last(struct meh_darray da);

extern void *
meh_darray_first(struct meh_darray da);

extern int
meh_darray_append(struct meh_darray *da, const void *item);

extern int
meh_darray_extend(struct meh_darray *da, void **items, size_t nitems);

extern size_t
meh_darray_len(struct meh_darray da);

extern size_t
meh_darray_blen(struct meh_darray da);

extern int
meh_darray_empty(struct meh_darray da);

extern int
meh_darray_non_empty(struct meh_darray da);

extern int
meh_darray_copy(struct meh_darray *dst, struct meh_darray src);

extern int
meh_darray_take(struct meh_darray *dst, struct meh_darray *src);

extern int
meh_darray_swap(struct meh_darray *dst, struct meh_darray *src);

extern void
meh_darray_print(struct meh_darray da, const char *name);

extern struct meh_darray
meh_darray_clone(struct meh_darray da);

extern int
meh_darray_resize(struct meh_darray *da, size_t newsz);

extern int
meh_darray_resize_item(struct meh_darray *da, size_t newsz);

#endif
