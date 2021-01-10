#include <lsys.h>
#include <psys.h>
#include <msys.h>

#include "dat.h"
#include "fns.h"

struct proc *
mkproc(void)
{
	struct proc *newproc;

	if(!proclist){
		newproc = proclist = allocpage();
		newproc->next = NULL;
	}
	else{
		newproc = allocpage();
		newproc->next = proclist;
		proclist = newproc;
	}

	newproc->lock = 0;
	newproc->pstate = RUNNABLE;

	newproc->msgbuf = allocpage();
	memset(newproc->msgbuf, 0, MSGBUFSZ);

	newproc->in = 0;
	newproc->out = 0;
	newproc->msgcondition = NOCONDITION;
	
	newproc->killswitch = 0;
	newproc->pid = newpid();

	return newproc;
}

	
