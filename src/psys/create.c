#include "dat.h"
#include "fns.h"

#include <hsys.h>
#include <lsys.h>
#include <msys.h>
#include <psys.h>

void
incarnate(void)
{
	if(currentproc == NULL)
		ultimateyeet("incarnate should be called from a new process!");

	release(&currentproc->lock);
	tohsys();
}

struct proc *
mkproc(char *name)
{
	struct proc *newproc;

	acquire(&proclistlock);

	if(!proclist){
		newproc = proclist = allocpage();
		if(!newproc) goto oompanic;
		memset(newproc, 0, sizeof(struct proc));
	}else{
		newproc = allocpage();
		if(!newproc) goto oompanic;

		memset(newproc, 0, sizeof(struct proc));
		newproc->next = proclist;
		proclist = newproc;
	}

	acquire(&newproc->lock);
	newproc->pid = newpid();
	release(&proclistlock);

	newproc->pstate = RUNNABLE;

	newproc->name = name;

	newproc->trapframe = allocpage();
	if(!newproc->trapframe) goto oompanic;
	memset(newproc->trapframe, 0, sizeof(struct trapframe));

	/* This is the most wild typecast ever (prototype from kapi/hsys.h) */
	newproc->trapframe->stg2 = utrap;
	newproc->trapframe->ksatp = (unsigned long)kpgtbl;

	newproc->upgtbl = mkupgtbl((char *)(newproc->trapframe));

	/* Set the scheduler context to run. */
	newproc->pkcontext.ra = (unsigned long)incarnate;

	/* Prepare per-process kernel stack  */
	newproc->ksbase = allocpage();
	memset(newproc->ksbase, 0, PAGESIZE);

	newproc->trapframe->ksp = (unsigned long)(newproc->ksbase) + PAGESIZE;
	newproc->pkcontext.sp = (unsigned long)(newproc->ksbase) + PAGESIZE;

	/* Done */
	return newproc;

oompanic:
	ultimateyeet("Out of memory!");
	return NULL;
}
