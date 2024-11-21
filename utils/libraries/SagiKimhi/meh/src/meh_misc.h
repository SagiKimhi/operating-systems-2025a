#ifndef MEH_MISC_H_
#define MEH_MISC_H_

#ifndef meh_cast
#define meh_cast(t, x) ((t)(x))
#endif

#ifndef meh_none
#define meh_none meh_cast(void, 0)
#endif

#ifndef meh_as_none
#define meh_as_none(x) meh_cast(void, (x))
#endif

#ifndef meh_swap
#define meh_swap(a, b) \
    do { \
        (a) = (a) ^ (b); \
        (b) = (b) ^ (a); \
        (a) = (a) ^ (b); \
    } while (0)
#endif

#ifndef meh_ptr_swap
#define meh_ptr_swap(pa, pb) \
    do { \
        (pa) = meh_cast(void *, meh_cast(size_t, pa) ^ meh_cast(size_t, pb)); \
        (pb) = meh_cast(void *, meh_cast(size_t, pb) ^ meh_cast(size_t, pa)); \
        (pa) = meh_cast(void *, meh_cast(size_t, pa) ^ meh_cast(size_t, pb)); \
    } while (0)
#endif

#endif
