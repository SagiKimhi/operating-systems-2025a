#include "process.h"

/* -----------------------------------------------------------------------------
 * Main
 * ----------------------------------------------------------------------------- */

int
main(void)
{
    Process p = process.get();
    process.fork(p, 10);
    process.print(p);
    process.join(p);
    return 0;
}

