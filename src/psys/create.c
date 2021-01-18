#include "dat.h"
#include "fns.h"

#include <hsys.h>
#include <lsys.h>
#include <msys.h>
#include <psys.h>

struct proc *
mkproc(void)
{
	struct proc *newproc;

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

	newproc->pstate = RUNNABLE;

	newproc->msgbuf = allocpage();
	if(!newproc->msgbuf) goto oompanic;
	memset(newproc->msgbuf, 0, MSGBUFSZ);

	newproc->msgcondition = NOCONDITION;

	newproc->pid = newpid();

	newproc->trapframe = allocpage();
	if(!newproc->trapframe) goto oompanic;
	memset(newproc->trapframe, 0, sizeof(struct trapframe));

	/* TODO: newproc->trapframe->stg2 = trap handler */

	newproc->upgtbl = mkupgtbl((char *)(newproc->trapframe));

	/* Set the scheduler context to run: TODO */
	/* newproc->pkcontext.ra = retfxn */
	return newproc;

oompanic:
	ultimateyeet("Out of memory!");
	return NULL;
}
