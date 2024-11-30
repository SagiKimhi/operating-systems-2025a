#ifndef MEH_H_
#define MEH_H_

#include "meh_api.h"

extern const struct meh_api meh;
extern const struct meh_bits_api meh_bits;
extern const struct meh_darray_api meh_darray;
extern const struct meh_process_api meh_process;

struct meh_api {
    struct meh_bits_api bits;
    struct meh_darray_api da;
    struct meh_process_api ps;
};

#ifdef MEH_SHORT_NAMESPACE
extern const struct meh_bits_api bits;
extern const struct meh_darray_api da;
extern const struct meh_process_api ps;
#endif

#endif
