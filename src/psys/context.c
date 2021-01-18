#include <psys.h>
#include <hsys.h>

#include "dat.h"
#include "fns.h"

/* hi i'm a coroutine (: */
void
yield(void)
{
	/* This will hit an S register upon the context
	 * switch thanks to the function call, so we can
	 * get it, call the switcheroo, and then restore.
	 */
	unsigned long myoldintrstate;

	/* Enter the global context, which throws
	 * into the infinite schedule loop of sad
	 * which never returns. We need to make
	 * sure of a few different things first.
	 */
	if(!currentproc) ultimateyeet("yield: already in globalcontext");
	if((currentproc->lock == 0) || (locksheld() != 1))
		ultimateyeet("yield: have to hold proc lock");
	if(currentproc->pstate == RUNNING)
		ultimateyeet("Boi why is you running in yield");
	
	/* Interrupts could break this, since this procs after a
	 * timer interrupt anyway. Could get us stuck or in a weird
	 * situation we aren't ready for, so exclude the possibility.
	 * Then again, we hold a lock, so interrupts should be off anyway.
	 * Never hurts to check.
	 */
	if(getsintr() == INTRON)
		ultimateyeet("We hold a lock, don't be interruptible :(");
	
	/* change da world, my final message, goodbye */
	myoldintrstate = getoldintrstate();	
	llcontextswitch(&currentproc->pkcontext, globalcontext);
	setoldintrstate(myoldintrstate);
}
