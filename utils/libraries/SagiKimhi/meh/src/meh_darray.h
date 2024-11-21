#ifndef MEH_DARRAY_H_
#define MEH_DARRAY_H_

#include "meh_api.h"
#include "meh_types.h"

/* -----------------------------------------------------------------------------
 * Macros
 * ----------------------------------------------------------------------------- */

#ifndef meh_da_print
#define meh_da_print(da) meh_darray_print(da, #da)
#endif

/* -----------------------------------------------------------------------------
 * Structs
 * ----------------------------------------------------------------------------- */

struct meh_darray {
    size_t size;
    size_t capacity;
    size_t item_size;
    void *items;
};

/* -----------------------------------------------------------------------------
 * Method Declarations
 * ----------------------------------------------------------------------------- */

extern meh_darray_t
meh_darray_create(size_t item_sz);

extern void
meh_darray_destroy(meh_darray_t *da);

extern int
meh_darray_get(meh_darray_t da, size_t index, void *dst);

extern int
meh_darray_set(meh_darray_t da, size_t index, const void *item);

extern int
meh_darray_append(meh_darray_t *da, const void *item);

extern int
meh_darray_extend(meh_darray_t *da, void **items, size_t nitems);

extern int
meh_darray_take(meh_darray_t *dst, meh_darray_t *src);

extern int
meh_darray_swap(meh_darray_t *dst, meh_darray_t *src);

extern int
meh_darray_copy(meh_darray_t *dst, meh_darray_t src);

extern meh_darray_t
meh_darray_clone(meh_darray_t da);

extern void
meh_darray_print(meh_darray_t da, const char *name);

extern int
meh_darray_resize(meh_darray_t *da, size_t newsz);

extern int
meh_darray_resize_item(meh_darray_t *da, size_t newsz);

#endif
