#include "process.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* -----------------------------------------------------------------------------
 * Defines
 * ----------------------------------------------------------------------------- */

#define readproc(p, proc) ((proc) = ((struct _process *)(p).self)[0])

/* -----------------------------------------------------------------------------
 * Structs
 * ----------------------------------------------------------------------------- */

struct _process {
    pid_t self;
    size_t num_children;
    pid_t children[MAX_GPROCS];
};

union _process_t {
    struct _process proc;
    char ptr[sizeof(struct _process)];
    int align;
};

/* -----------------------------------------------------------------------------
 * Static Methods
 * ----------------------------------------------------------------------------- */

static void
report_process_err(pid_t pid);

static void
report_child_created(pid_t pid, pid_t cpid);

static void
report_child_exit_status(pid_t pid, pid_t cpid, int status);

/* -----------------------------------------------------------------------------
 * API Implementation
 * ----------------------------------------------------------------------------- */

Process
getp(void)
{
    Process p = process;
    union _process_t _p = {0};
    _p.proc.self = getpid();
    p.self = _p.ptr;
    return p;
}

void
nfork(Process p, size_t n)
{
    pid_t pid;
    struct _process proc;

    readproc(p, proc);

    while (proc.num_children < n && (pid = fork()) > 0) {
        proc.children[proc.num_children++] = pid;
        report_child_created(proc.self, pid);
    };

    if (pid < 0)
        report_process_err(proc.self);
}

void
join(Process p)
{
    pid_t pid;
    int status;
    struct _process proc;

    readproc(p, proc);

    if (getpid() != proc.self)
        return;

    pid = status = 0;

    while (pid >= 0 && proc.num_children > 0) {
        pid = waitpid(proc.children[proc.num_children - 1], &status, WNOHANG);

        if (pid > 0) {
            proc.num_children--;
            report_child_exit_status(proc.self, pid, status);
        }
    }

    if (pid < 0)
        report_process_err(proc.self);
}

void
printp(Process p)
{
    size_t i;
    struct _process proc;

    readproc(p, proc);

    if (getpid() != proc.self)
        return;

    fprintf(stdout, "\n");
    fprintf(stdout, "INFO(pid-%0d): num_children=%0lu\n", proc.self,
        proc.num_children);

    for (i = 0; i < proc.num_children; i++) {
        fprintf(stdout, "INFO(pid-%0d): children[%0lu]=%0d\n", proc.self, i,
            proc.children[i]);
    }
    fprintf(stdout, "\n");
}

/* -----------------------------------------------------------------------------
 * Static Method Implementation
 * ----------------------------------------------------------------------------- */

static void
report_process_err(pid_t pid)
{
    fprintf(stderr, "ERROR(pid-%0d):", pid);
    perror("");
}

static void
report_child_created(pid_t pid, pid_t cpid)
{
    fprintf(
        stdout, "INFO(pid-%0d): created child process pid-%0d\n", pid, cpid);
}

static void
report_child_exit_status(pid_t pid, pid_t cpid, int status)
{
    fprintf(stdout, "INFO(pid-%0d): child pid-%0d finished (status=%0d)\n", pid,
        cpid, status);
}
