#include <bits/types.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "meh_darray.h"
#include "meh_io.h"
#include "meh_math.h"
#include "meh_mem.h"
#include "meh_misc.h"

/* -----------------------------------------------------------------------------
 * Static Method Declarations
 * ----------------------------------------------------------------------------- */

static int
darray_is_valid(meh_darray_t da);

static int
darray_is_allocated(meh_darray_t da);

static int
darray_is_item_valid(const void *item);

static int
darray_is_index_valid(meh_darray_t da, size_t index);

static int
darray_is_item_size_valid(size_t sz);

/* -----------------------------------------------------------------------------
 * Macros and Defines
 * ----------------------------------------------------------------------------- */

#define DARRAY_INIT_CAP __WORDSIZE

#define DARRAY_RESIZE_FACTOR 2

#define darray_item_at(da, index) ((da).items + ((index) * (da).item_size))

#define darray_byte_size(da) ((da).size * (da).item_size)

#define darray_byte_capacity(da) ((da).capacity * (da).item_size)

#define darray_ensure_not_null(ptr, ret) \
    meh_ensure((ptr) != NULL, ret, "argument '" #ptr "' is NULL.");

#define darray_ensure_item_valid(item, ret) \
    meh_ensure(                             \
        darray_is_item_valid(item),         \
        ret,                                \
        "argument '" #item "' is NULL and does not point to a valid value.")

#define darray_ensure_index_valid(da, index, ret)                           \
    meh_ensure(                                                             \
        darray_is_index_valid((da), index),                                 \
        ret,                                                                \
        "argument 'index' is larger than the size of the array pointed to " \
        "by argument 'da'.")

#define darray_ensure_item_size_valid(sz, ret) \
    meh_ensure(                                \
        darray_is_item_size_valid(sz), ret, #sz " must be greater than 0")

#define darray_ensure_valid(da, ret) \
    meh_ensure(darray_is_valid(da), ret, "argument '" #da "' is invalid.")

#define darray_ensure_empty(da, ret) \
    meh_ensure(darray_is_empty(da), ret, "argument '" #da "' is non-empty.")

#define darray_ensure_non_empty(da, ret) \
    meh_ensure(!darray_is_empty(da), ret, "argument '" #da "' is empty.")

#define darray_ensure_allocated(da, ret) \
    meh_ensure(                          \
        darray_is_allocated((da)), ret, "argument '" #da "' is unallocated.")

#define darray_ensure_reallocated(da, ret, sz)                \
    meh_ensure(                                               \
        ((da).items = meh_realloc((da).items, (sz))) != NULL, \
        ret,                                                  \
        "buy more ram lol")

/* -----------------------------------------------------------------------------
 * Public Method Definitions
 * ----------------------------------------------------------------------------- */

meh_darray_t
meh_darray_create(size_t item_sz)
{
    darray_ensure_item_size_valid(item_sz, (meh_darray_t){0});
    return (meh_darray_t){
        .size = 0,
        .capacity = 0,
        .item_size = item_sz,
        .items = NULL,
    };
}

void
meh_darray_destroy(meh_darray_t *da)
{
    if (da == NULL)
        return;

    if (darray_is_allocated(*da))
        meh_free(da->items);

    da->size = 0;
    da->capacity = 0;
    da->items = NULL;
}

int
meh_darray_get(meh_darray_t da, size_t index, void *dst)
{
    darray_ensure_valid(da, 0);
    darray_ensure_allocated(da, 0);
    darray_ensure_index_valid(da, index, 0);
    darray_ensure_item_valid(dst, 0);
    memcpy(dst, darray_item_at(da, index), da.item_size);
    return 1;
}

int
meh_darray_set(meh_darray_t da, size_t index, const void *item)
{
    darray_ensure_valid(da, 0);
    darray_ensure_allocated(da, 0);
    darray_ensure_index_valid(da, index, 0);
    darray_ensure_item_valid(item, 0);
    memcpy(darray_item_at(da, index), item, da.item_size);
    return 1;
}

int
meh_darray_append(meh_darray_t *da, const void *item)
{
    darray_ensure_not_null(da, 0);

    if (meh_darray_resize(da, da->size + 1)) {
        if (meh_darray_set(*da, da->size - 1, item))
            return 1;

        da->size--;
    }

    return 0;
}

int
meh_darray_extend(meh_darray_t *da, void **items, size_t nitems)
{
    size_t idx;
    size_t offset;

    darray_ensure_not_null(da, 0);
    darray_ensure_item_valid(items, 0);

    if (meh_darray_resize(da, da->size + nitems)) {
        for (idx = da->size - nitems; idx < da->size; idx++) {
            offset = da->item_size * (da->size - idx);

            if (!meh_darray_set(*da, idx, items[0] + offset))
                break;
        }

        nitems = da->size - idx;

        if (nitems)
            da->size -= nitems;
    }

    return nitems;
}

int
meh_darray_take(meh_darray_t *dst, meh_darray_t *src)
{
    meh_darray_destroy(dst);
    return meh_darray_swap(dst, src);
}

int
meh_darray_swap(meh_darray_t *dst, meh_darray_t *src)
{
    darray_ensure_not_null(src, 0);
    darray_ensure_not_null(dst, 0);
    meh_swap(dst->size, src->size);
    meh_swap(dst->capacity, src->capacity);
    meh_swap(dst->item_size, src->item_size);
    meh_ptr_swap(dst->items, src->items);
    return 1;
}

int
meh_darray_copy(meh_darray_t *dst, meh_darray_t src)
{
    if (!meh_darray_resize_item(dst, src.item_size))
        return 0;

    if (!meh_darray_resize(dst, src.size))
        return 0;

    memcpy(dst->items, (const void *)src.items, darray_byte_size(src));
    return 1;
}

meh_darray_t
meh_darray_clone(meh_darray_t da)
{
    meh_darray_t _da;

    darray_ensure_valid(da, (meh_darray_t){0});

    _da = meh_darray_create(da.item_size);
    return meh_darray_copy(&_da, da) ? _da : (meh_darray_t){0};
}

void
meh_darray_print(meh_darray_t da, const char *name)
{
    void *p;

    darray_ensure_valid(da, meh_none);

    if (!name)
        name = "darray";

    p = da.items;

    fprintf(stdout, "%s.size=%zu\n", name, da.size);
    fprintf(stdout, "%s.capacity=%zu\n", name, da.capacity);
    fprintf(stdout, "%s.item_size=%zu\n", name, da.item_size);
    fprintf(stdout, "%s.items=%s\n", name, p ? "[" : "NULL");

    if (!p)
        return;

    while (da.size > 1) {
        fprintf(stdout, "%p, ", p);
        da.size--;
        p += da.item_size;
    }

    if (da.size)
        fprintf(stdout, "%p", p);

    fprintf(stdout, "]\n");
}

int
meh_darray_resize(meh_darray_t *da, size_t newsz)
{
    darray_ensure_not_null(da, 0);
    darray_ensure_valid(*da, 0);

    if (da->capacity < newsz) {
        size_t newcap = meh_max(da->capacity, DARRAY_INIT_CAP);

        while (newcap < newsz)
            newcap *= DARRAY_RESIZE_FACTOR;

        darray_ensure_reallocated(*da, 0, newcap * da->item_size);
        da->capacity = newcap;
    }

    if (da->size != newsz)
        da->size = newsz;

    return 1;
}

int
meh_darray_resize_item(meh_darray_t *da, size_t newsz)
{
    darray_ensure_not_null(da, 0);

    if (da->item_size != newsz) {
        darray_ensure_valid(*da, 0);
        darray_ensure_item_size_valid(newsz, 0);
        darray_ensure_reallocated(*da, 0, da->capacity * newsz);
        da->size = darray_byte_size(*da) / newsz;
        da->item_size = newsz;
    }

    return 1;
}

void *
darray_buffer(meh_darray_t da)
{
    return da.items;
}

/* -----------------------------------------------------------------------------
 * Static Method Definitions
 * ----------------------------------------------------------------------------- */

static int
darray_is_valid(meh_darray_t da)
{
    return da.item_size > 0 && da.capacity >= da.size
           && ((da.capacity == 0 && da.items == NULL)
               || darray_is_allocated(da));
}

static int
darray_is_allocated(meh_darray_t da)
{
    return da.capacity > 0 && da.items != NULL;
}

static int
darray_is_item_valid(const void *item)
{
    return item != NULL;
}

static int
darray_is_index_valid(meh_darray_t da, size_t index)
{
    return index < da.size;
}

static int
darray_is_item_size_valid(size_t sz)
{
    return sz > 0;
}
