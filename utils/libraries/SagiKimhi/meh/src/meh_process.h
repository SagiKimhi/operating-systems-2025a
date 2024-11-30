#ifndef MEH_PROCESS_H_
#define MEH_PROCESS_H_

#include <sys/types.h>
#include "meh_darray.h"

#define meh_process_print(p) meh_process_print_(p, #p)

struct meh_process {
    pid_t pid;
    pid_t ppid;
    struct meh_darray children;
};

struct meh_process_list {
    size_t len;
    struct meh_process *ps;
};

/* -----------------------------------------------------------------------------
 * Method Declarations
 * ----------------------------------------------------------------------------- */

extern struct meh_process
meh_process_self(void);

extern struct meh_process
meh_process_init(pid_t pid, pid_t ppid);

extern void
meh_process_destroy(struct meh_process *p);

extern struct meh_process *
meh_process_child(struct meh_process *p, size_t i);

extern struct meh_process_list
meh_process_children(void);

extern size_t
meh_process_num_children(struct meh_process p);

extern int
meh_process_fork(struct meh_process *p, size_t nchildren);

extern int
meh_process_join(struct meh_process *p);

extern int
meh_process_join_any(struct meh_process *p);

extern void
meh_process_join_none(struct meh_process *p);

extern void
meh_process_print_(struct meh_process p, char *name);

#endif
