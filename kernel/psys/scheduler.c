#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <lsys.h>
#include <msys.h>
#include <psys.h>

/* the os scheduler, in its glory
 * "jay, you really could do better than this"
 * #codegolf
 */

struct kcontext *globalcontext;

void
scheduler(void)
{
	struct proc *p;
	struct kcontext sglobalcontext;
	unsigned long intrstate;

	/* Set up the global context on the scheduler
	 * stack, since it'll be relatively untouched here
	 * I'm not worried about stackoverflows but maybe I
	 * should be? We shall see
	 */
	globalcontext = &sglobalcontext;

	currentproc = NULL;
	if(getsintr() == INTROFF)
		ultimateyeet("scheduler should be interruptible");

	for(;;){
		for(p = proclist; p != NULL; p = p->next){
			acquire(&p->lock);
			if(p->pstate == RUNNABLE){
				uartwrite("Switching to process: ");
				uartwrite(p->name);
				uartwrite("\n");

				p->pstate = RUNNING;
				currentproc = p;

				intrstate = getoldintrstate();
				llcontextswitch(globalcontext, &p->pkcontext);
				setoldintrstate(intrstate);

				currentproc = NULL;
			}else{
				uartwrite("Skipping process ");
				uartwrite(p->name);
				uartwrite(": not runnable\n");
			}
			release(&p->lock);
		}
	}
}
