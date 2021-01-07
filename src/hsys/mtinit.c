#include <hsys.h>

#include "dat.h"
#include "fns.h"

struct tinfo timerscratch;

unsigned long
mktimerscratch(void)
{
    int i;
    unsigned long *tsp;

    /* Initial interrupt timing. For now, this is one second */
    for(i = 0; i < 3; i++) timerscratch.fakestack[i] = 0;
    timerscratch.mtimecmpaddr = MTIMECMP;
    timerscratch.mtimeaddr = MTIME;
    timerscratch.interval = TIMERINTERVAL;

    /* Return tsp to the caller */
    tsp = (unsigned long *)&timerscratch;
    return (unsigned long)tsp;
}