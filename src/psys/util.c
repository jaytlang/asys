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

void
procinit(void)
{
	pidlock = 0;
	proclistlock = 0;
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

void *
exporttrapframe(void)
{
	struct trapframe *tf;

	/* Configure the trap frame for a return
	 * to userspace. Must be run from a process
	 * context else bad things happen.
	 */
	if(currentproc == NULL)
		ultimateyeet("exporttrapframe ran from global context");

	/* The only thing we really need to do to tf
	 * is to set the right epc. stg2 is hardcoded
	 * in every process trapframe page on proc creation,
	 * and other regs have already been saved. it's possible
	 * that sepc is tweaked by us out of hsys so it needs updating
	 */
	tf = currentproc->trapframe;

	/* Trap frame is ready for export */
	return (void *)tf;
}

unsigned long *
exportupgtbl(void)
{
	/* Same deal, but for the page table */
	if(currentproc == NULL)
		ultimateyeet("exportupgtbl ran from global context");
	return currentproc->upgtbl;
}
