#include <psys.h>
#include <hsys.h>
#include <dsys.h>

#include "dat.h"
#include "fns.h"


void
yield(void)
{
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
		ultimateyeet("Whymst is the scheduler interruptible?");
	
	
	
}
