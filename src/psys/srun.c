#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <lsys.h>
#include <msys.h>
#include <psys.h>

unsigned long
srun(unsigned long entrypt, unsigned long start, unsigned long end, char *name)
{
	char *prgrmpage, *vpage, *tgtpage;
	struct proc *new;
	unsigned long prgrmsize;
	unsigned long entrydelta;
	int foundepc;

	if(end <= start) ultimateyeet("Bad program start/end!");
	if(!name) ultimateyeet("Bad name");
	if(entrypt < start || entrypt >= end) ultimateyeet("bad entrypt!");

	prgrmsize = end - start;

	/* Prepare the new process structure. Here it is added
	 * to the scheduler's list of processes to run (at the head),
	 * we grab the lock on the process, and all fields are
	 * initialized.
	 */
	new = mkproc(name);

	/* In the name of isolation, we won't map user code (in
	 * the kernel text) directly into userland. We will instead
	 * copy it to remain faithful to security. Let's make room...
	 */
	mkuserpages(new->upgtbl, 0, prgrmsize, MEMTYPE_CODE);

	/* Ok. VAs are simple - start from zero and work our way up
	 * to end-start. The PAs are start->end in contiguous order.
	 * With a walk primitive, this is simple...
	 */
	foundepc = 0;

	prgrmpage = (char *)start;
	for(vpage = 0; vpage < (char *)prgrmsize;
	    vpage += PAGESIZE, prgrmpage += PAGESIZE){
		/* Get the target we'll copy to */
		tgtpage = (char *)translateva(new->upgtbl, vpage);
		if(!tgtpage)
			ultimateyeet("should have va mapped that we don't!");

		/* Target acquired. Copy data from prgrmpage to tgtpage */
		memcpy(tgtpage, prgrmpage, PAGESIZE);

		/* Check for the entrypoint */
		if(entrypt >= (unsigned long)prgrmpage &&
		   entrypt < (unsigned long)prgrmpage + PAGESIZE){
			entrydelta = entrypt - (unsigned long)prgrmpage;
			new->trapframe->epc = (unsigned long)vpage + entrydelta;
			foundepc = 1;
		}
	}

	/* did we land on the entrypoint or is something really bad here? */
	if(!foundepc) ultimateyeet("no entrypoint somehow");

	/* make the guard page and the user stack */
	new->memsize = prgrmsize + 2 * PAGESIZE;
	mkuserpages(new->upgtbl, prgrmsize, prgrmsize + PAGESIZE,
	            MEMTYPE_GUARD);
	mkuserpages(new->upgtbl, prgrmsize + PAGESIZE, new->memsize,
	            MEMTYPE_DATA);

	new->trapframe->sp = (unsigned long)translateva(
	    new->upgtbl, (char *)(new->memsize - PAGESIZE));
	if(!new->trapframe->sp)
		ultimateyeet("failed to set sp in new srun'd process!");

	/* Donezo! */
	release(&new->lock);
	return new->pid;
}
