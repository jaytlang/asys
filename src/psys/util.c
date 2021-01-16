#include <lsys.h>
#include <hsys.h>
#include <psys.h>

#include "dat.h"
#include "fns.h"

char *globalkstack;

struct proc *proclist;
struct proc *currentproc;

unsigned long toppid;
unsigned int pidlock;

void
procinitwith(char *kstack)
{
	globalkstack = kstack;
	pidlock = 0;
	toppid = 0; 

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
	