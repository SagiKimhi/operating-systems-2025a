#ifndef MEH_API_H_
#define MEH_API_H_

#include "meh_io.h"
#include "meh_mem.h"
#include "meh_math.h"
#include "meh_bits.h"
#include "meh_fork.h"
#include "meh_misc.h"
#include "meh_types.h"
#include "meh_compat.h"
#include "meh_darray.h"
#include "meh_process.h"

/* -----------------------------------------------------------------------------
 * Bits API Definition
 * ----------------------------------------------------------------------------- */

struct meh_bits_api {
    /* Manipulations */

    meh_bitvec_t (*get)(meh_word_t val, size_t high, size_t low);

    meh_bitvec_t (*set)(meh_word_t dst, size_t high, size_t low, meh_word_t src);

    meh_bitvec_t (*toggle)(meh_word_t val, size_t high, size_t low);

    /* Operations */

    size_t (*countones)(meh_word_t value);

    size_t (*countzeros)(meh_word_t value);

    /* Policies */

    int (*compare)(
        meh_word_t a,
        meh_word_t ah,
        meh_word_t al,
        meh_word_t b,
        meh_word_t bh,
        meh_word_t bl);
};

/* -----------------------------------------------------------------------------
 * Darray API Definition
 * ----------------------------------------------------------------------------- */

struct meh_darray_api {
    /* Constructor */

    meh_darray_t (*create)(size_t item_sz);

    /* Destructor */

    void (*destroy)(meh_darray_t *da);

    /* Getters and Setters */

    void *(*get)(meh_darray_t da, size_t index);

    void *(*pop)(meh_darray_t *da);

    void *(*last)(meh_darray_t da);

    void *(*first)(meh_darray_t da);

    int (*set)(meh_darray_t da, size_t index, const void *item);

    int (*append)(meh_darray_t *da, const void *item);

    int (*extend)(meh_darray_t *da, void **items, size_t nitems);

    /* Inquries */

    size_t (*len)(meh_darray_t da);

    size_t (*blen)(meh_darray_t da);

    int (*empty)(meh_darray_t da);

    int (*non_empty)(meh_darray_t da);

    /* Field Policies */

    int (*copy)(meh_darray_t *dst, meh_darray_t src);

    int (*take)(meh_darray_t *dst, meh_darray_t *src);

    int (*swap)(meh_darray_t *dst, meh_darray_t *src);

    void (*print)(meh_darray_t da, const char *optional_name);

    meh_darray_t (*clone)(meh_darray_t da);

    /* Low Level Interface */

    int (*resize)(meh_darray_t *da, size_t newsz);

    int (*resize_item)(meh_darray_t *da, size_t newsz);
};

/* -----------------------------------------------------------------------------
 * Process API Definition
 * ----------------------------------------------------------------------------- */

struct meh_process_api {
    /* Constructor/Destructor */

    meh_process_t (*self)(void);
    meh_process_t (*init)(pid_t pid, pid_t ppid);
    void (*destroy)(meh_process_t *p);

    /* Hierarchy */

    meh_process_t *(*last)(void);
    meh_process_t *(*first)(void);
    meh_process_t *(*child)(meh_process_t *p, size_t voidi);
    meh_process_list_t (*children)(void);
    size_t (*num_children)(meh_process_t p);

    meh_process_t *(*plast)(meh_process_t *p);
    meh_process_t *(*pfirst)(meh_process_t *p);
    meh_process_t *(*pchild)(meh_process_t *p, size_t i);
    meh_process_t **(*pchildren)(meh_process_t p);
    size_t (*num_pchildren)(meh_process_t p);

    /* Fork-Join */

    int (*fork)(meh_process_t *p, size_t nchildren);
    int (*join)(meh_process_t *p);
    int (*join_any)(meh_process_t *p);
    void (*join_none)(meh_process_t *p);

    /* Policies */

    void (*print)(meh_process_t p, char *name);
};

#endif
