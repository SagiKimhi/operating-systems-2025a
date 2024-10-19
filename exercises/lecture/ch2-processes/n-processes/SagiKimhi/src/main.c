#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_GPROCS 100

typedef struct process_group {
    pid_t self;
    pid_t children[MAX_GPROCS];
    size_t num_children;
} ProcessGroup;

int
is_pparent(pid_t id)
{
    return id > 0;
}

int
is_pchild(pid_t id)
{
    return id == 0;
}

int is_perr(pid_t id)
{
    return id < 0;
}

ProcessGroup
new_pgroup(void)
{
    return (ProcessGroup) {
        .self=getpid(),
        .num_children=0,
        .children = {-1}
    };
}

ProcessGroup
fork_n(size_t n)
{
    /* int i; */
    pid_t id;
    ProcessGroup proc = new_pgroup();

    if (!n)
        return proc;

    do {
        id = fork();

        if (is_pparent(id)) {
            proc.children[proc.num_children++] = id;
            fprintf(
                stdout, 
                "PID %0d: created process no. %lu with id %0d.\n", 
                proc.self, proc.num_children, id
            );
            id = proc.self;
        }
    } while (id == proc.self && proc.num_children < n);

    if (is_pchild(id)) {
        fprintf(stdout, "Hello and goodbye from child pid %0d\n", getpid());
        exit(0);
    }

    if (is_perr(id)) {
        fprintf(stderr, "fork returned -1 for pid %0d", getpid());
        exit(1);
    }

    return proc;
}

void
join(ProcessGroup proc)
{
    pid_t pid;
    int status;

    while (proc.num_children > 0) {
        pid = proc.children[proc.num_children];
        pid = waitpid(pid, &status, WNOHANG);

        if (pid == 0)
            continue;

        if (pid > 0) {
            fprintf(
                stdout, "wait for pid %0d finished with status %0d\n", pid, status
            );
        }
        else {
            fprintf(
                stderr, "wait for pid %0d failed with status %0d\n", pid, status
            );
        }

        proc.num_children--;
    }
}

int main(void)
{
    ProcessGroup g;
    
    g = fork_n(5);
    join(g);

	return 0;
}
