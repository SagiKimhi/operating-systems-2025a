#ifndef _MEH_FORK_H
#define _MEH_FORK_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "meh_io.h"
#include <stdio.h>

#define meh_fork(...)  \
    do {               \
        pid_t pid = 0; \
    (void)(0)

#define meh_begin(...)                                    \
    pid = fork();                                         \
                                                          \
    if (pid == -1) {                                      \
        meh_fatal("pid-%0d: fork failed\n", getpid());    \
        _exit(-1);                                        \
    }                                                     \
                                                          \
    if (pid == 0) {                                       \
        meh_debug("pid-%0d: process started.", getpid()); \
    (void)(0)
#define meh_end(...)                                 \
    meh_debug("pid-%0d: process ending.", getpid()); \
    _exit(0);                                        \
    }                                                \
    (void)(0)

#define meh_join(...)                                       \
    if (pid > 0) {                                          \
        pid_t _pid = 0;                                     \
        while ((_pid = waitpid(pid, NULL, WNOHANG)) >= 0) { \
            sleep(0);                                       \
        }                                                   \
    }                                                       \
    }                                                       \
    while (0)

#define meh_join_any(...)                                   \
    if (pid > 0) {                                          \
        pid_t _pid = 0;                                     \
        while ((_pid = waitpid(pid, NULL, WNOHANG)) == 0) { \
            sleep(0);                                       \
        }                                                   \
    }                                                       \
    }                                                       \
    while (0)

#define meh_join_none(...)                                    \
    if (pid > 0) {                                            \
        if (waitpid(pid, NULL, WNOHANG) == -1) {              \
            meh_fatal("pid-%0d: waitpid failed\n", getpid()); \
            _exit(-1);                                        \
        }                                                     \
    }                                                         \
    }                                                         \
    while (0)

#endif
