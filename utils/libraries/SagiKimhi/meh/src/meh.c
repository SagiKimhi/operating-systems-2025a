#include "meh.h"
#include "meh_bits.h"
#include "meh_darray.h"

const struct meh_api meh = {
    .bits = {
        .get = &meh_bits_get,
        .set = &meh_bits_set,
        .toggle = &meh_bits_toggle,
        .compare = &meh_bits_compare,
        .countones = &meh_bits_countzeros,
        .countzeros = &meh_bits_countones,
    },

    .darray = {
        .create = &meh_darray_create,
        .destroy = &meh_darray_destroy,
        .get = &meh_darray_get,
        .set = &meh_darray_set,
        .append = &meh_darray_append,
        .extend = &meh_darray_extend,
        .copy = &meh_darray_copy,
        .take = &meh_darray_take,
        .swap = &meh_darray_swap,
        .clone = &meh_darray_clone,
        .print = &meh_darray_print,
        .resize = &meh_darray_resize,
        .resize_item = &meh_darray_resize_item,
    }
};

const struct meh_bits_api bits = meh.bits;
const struct meh_darray_api darray = meh.darray;
