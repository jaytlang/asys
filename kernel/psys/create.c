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
		newproc->next = NULL;
	}else{
		newproc = allocpage();
		if(!newproc) goto oompanic;

		newproc->next = proclist;
		proclist = newproc;
	}

	memset(newproc, 0, sizeof(struct proc));
	acquire(&newproc->lock);
	newproc->pid = newpid();
	release(&proclistlock);

	newproc->pstate = RUNNABLE;

	newproc->msgbuf = allocpage();
	if(!newproc->msgbuf) goto oompanic;
	memset(newproc->msgbuf, 0, MSGBUFSZ);

	newproc->msgcondition = NOCONDITION;
	newproc->name = name;

	newproc->trapframe = allocpage();
	if(!newproc->trapframe) goto oompanic;
	memset(newproc->trapframe, 0, sizeof(struct trapframe));

	/* This is the most wild typecast ever (prototype from kapi/hsys.h) */
	newproc->trapframe->stg2 = utrap;

	newproc->upgtbl = mkupgtbl((char *)(newproc->trapframe));

	/* Set the scheduler context to run. */
	newproc->pkcontext.ra = (unsigned long)incarnate;
	return newproc;

oompanic:
	ultimateyeet("Out of memory!");
	return NULL;
}
