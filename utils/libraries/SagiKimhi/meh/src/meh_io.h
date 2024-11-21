#ifndef MEH_REPORT_MACROS_H_
#define MEH_REPORT_MACROS_H_

#include <stdarg.h>

#ifndef meh_log
#define meh_log(fd, TAG, ...)                            \
    do {                                                 \
        fprintf(fd, TAG);                                \
        fprintf(fd, __VA_ARGS__);                        \
        fprintf(fd, "(%s, %0d).\n", __FILE__, __LINE__); \
    } while (0)
#endif

#ifndef meh_info
#define meh_info(TAG, ...) \
    meh_log(stdout, "INFO (" #TAG " failed): ", __VA_ARGS__)
#endif

#ifndef meh_error
#define meh_error(TAG, ...) \
    meh_log(stderr, "ERROR (" #TAG " failed): ", __VA_ARGS__)
#endif

#ifndef meh_check
#define meh_check(cond, ...)            \
    if (!(cond)) {                      \
        meh_error((cond), __VA_ARGS__); \
    }
#endif

#ifndef meh_ensure
#define meh_ensure(cond, ret, ...)      \
    if (!(cond)) {                      \
        meh_error((cond), __VA_ARGS__); \
        return ret;                     \
    }
#endif

#endif
