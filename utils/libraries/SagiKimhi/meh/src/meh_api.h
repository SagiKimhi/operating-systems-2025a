#ifndef MEH_API_H_
#define MEH_API_H_

#include "meh_types.h"

/* -----------------------------------------------------------------------------
 * Bits API Definition
 * ----------------------------------------------------------------------------- */

struct meh_bits_api {
    /* Common Manipulations */

    meh_bitvec_t (*get)(meh_word_t val, size_t high, size_t low);

    meh_bitvec_t (*set)(meh_word_t dst, size_t high, size_t low, meh_word_t src);

    meh_bitvec_t (*toggle)(meh_word_t val, size_t high, size_t low);

    /* Bit Vector Comparison */

    int (*compare)(
        meh_word_t a,
        meh_word_t ah,
        meh_word_t al,
        meh_word_t b,
        meh_word_t bh,
        meh_word_t bl);

    /* Bit Vector Utilities */

    size_t (*countones)(meh_word_t value);

    size_t (*countzeros)(meh_word_t value);
};

/* -----------------------------------------------------------------------------
 * Darray API Definition
 * ----------------------------------------------------------------------------- */

struct meh_darray_api {

    /* Constructor */

    meh_darray_t (*create)(size_t item_sz);

    /* Destructor */

    void (*destroy)(meh_darray_t *da);

    /* Data Manipulation */

    int (*get)(meh_darray_t da, size_t index, void *dst);

    int (*set)(meh_darray_t da, size_t index, const void *item);

    int (*append)(meh_darray_t *da, const void *item);

    int (*extend)(meh_darray_t *da, void **items, size_t nitems);

    /* Dynamic Array Policies */

    int (*take)(meh_darray_t *dst, meh_darray_t *src);

    int (*swap)(meh_darray_t *dst, meh_darray_t *src);

    int (*copy)(meh_darray_t *dst, meh_darray_t src);

    meh_darray_t (*clone)(meh_darray_t da);

    void (*print)(meh_darray_t da, const char *optional_name);

    /* Low Level Interface */

    int (*resize)(meh_darray_t *da, size_t newsz);

    int (*resize_item)(meh_darray_t *da, size_t newsz);
};

#endif
