#ifndef MEH_H_
#define MEH_H_

#include "meh_io.h"
#include "meh_api.h"
#include "meh_mem.h"
#include "meh_bits.h"
#include "meh_math.h"
#include "meh_misc.h"
#include "meh_types.h"
#include "meh_darray.h"

/* -----------------------------------------------------------------------------
 * API Access Variables
 * ----------------------------------------------------------------------------- */

#ifndef MEH_SHORT_NAMESPACES
extern const struct meh_api meh;
#else
extern const struct meh_api meh;
extern const struct meh_bits_api bits;
extern const struct meh_darray_api darray;
#endif

/* -----------------------------------------------------------------------------
 * API Definition
 * ----------------------------------------------------------------------------- */

struct meh_api {
    struct meh_bits_api bits;
    struct meh_darray_api darray;
};

#endif
