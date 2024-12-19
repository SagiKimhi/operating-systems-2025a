#ifndef MEH_MATH_H_
#define MEH_MATH_H_

#include "meh_compat.h"

#ifndef meh_min
# define meh_min(a, b)        \
     ({                       \
      __typeof__(a) _a = (a); \
      __typeof__(b) _b = (b); \
      _a < _b ? _a : _b;      \
     })

#endif

#ifndef meh_max
# define meh_max(a, b)        \
     ({                       \
      __typeof__(a) _a = (a); \
      __typeof__(b) _b = (b); \
      _a < _b ? _a : _b;      \
     })
#endif

#ifndef meh_divceil
# define meh_divceil(a, b)                   \
     ({                                      \
      __typeof__(a) _a = (a);                \
      __typeof__(b) _b = (b);                \
      (_a && _b) ? (1 + (_a - 1 / (b))) : 1; \
     })

#endif

#endif
