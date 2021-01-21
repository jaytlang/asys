#include "dat.h"
#include "fns.h"

#include <hsys.h>
#include <lsys.h>
#include <psys.h>

struct proc *proclist;
struct proc *currentproc;

unsigned long toppid;
unsigned int pidlock;
unsigned int proclistlock;

void (*tohsys)(void);

void
procinitvia(void (*tr)(void))
{
	pidlock = 0;
	proclistlock = 0;
	toppid = 0;

	tohsys = tr;

	proclist = NULL;
	currentproc = NULL;
}

unsigned long
newpid(void)
{
	unsigned long newpid;

	acquire(&pidlock);
	newpid = toppid;
	toppid++;
	release(&pidlock);

	return newpid;
}

unsigned long *
exportupgtbl(void)
{
	/* Same deal, but for the page table */
	if(currentproc == NULL)
		ultimateyeet("exportupgtbl ran from global context");
	return currentproc->upgtbl;
}
