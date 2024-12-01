#include "meh_bits.h"
#include "meh_darray.h"
#include "meh_process.h"
#include "meh.h"

const struct meh_api meh = {
    .bits = {
        .get =  &meh_bits_get,
        .set = &meh_bits_set,
        .toggle = &meh_bits_toggle,
        .compare = &meh_bits_compare,
        .countones = &meh_bits_countzeros,
        .countzeros = &meh_bits_countones,
    },

    .darray = {
        .create = &meh_darray_create_,
        .destroy = &meh_darray_destroy,
        .get = &meh_darray_get,
        .pop = &meh_darray_pop,
        .last = &meh_darray_last,
        .first = &meh_darray_first,
        .set = &meh_darray_set,
        .append = &meh_darray_append,
        .extend = &meh_darray_extend,
        .len=&meh_darray_len,
        .blen=&meh_darray_blen,
        .empty=&meh_darray_empty,
        .non_empty=&meh_darray_non_empty,
        .clone = &meh_darray_clone,
        .copy = &meh_darray_copy,
        .take = &meh_darray_take,
        .swap = &meh_darray_swap,
        .print = &meh_darray_print,
        .resize = &meh_darray_resize,
        .resize_item = &meh_darray_resize_item,
    },

    .process = {
        .self = &meh_process_self,
        .init = &meh_process_init,
        .destroy=&meh_process_destroy,
        .child = &meh_process_child,
        .children = &meh_process_children,
        .num_children = &meh_process_num_children,
        .fork = &meh_process_fork,
        .join = &meh_process_join,
        .join_any = &meh_process_join_any,
        .join_none = &meh_process_join_none,
        .print = &meh_process_print_,
    },
};
