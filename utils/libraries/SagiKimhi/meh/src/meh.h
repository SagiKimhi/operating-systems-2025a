#ifndef MEH_H_
#define MEH_H_

#include "meh_api.h"

/* -----------------------------------------------------------------------------
 * API Declaration
 * ----------------------------------------------------------------------------- */

extern const struct meh_api meh;

/* -----------------------------------------------------------------------------
 * API Definition
 * ----------------------------------------------------------------------------- */

struct meh_api {
    struct meh_bits_api bits;
    struct meh_darray_api darray;
    struct meh_process_api process;
};

#ifdef MEH_SHORT_NAMESPACE
# define da meh.darray
# define ps meh.process
# define bits meh.bits
#endif

#endif
