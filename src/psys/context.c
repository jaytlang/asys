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
	if(currentproc->lock == 0) ultimateyeet("yield: have to hold proc lock");
	if(currentproc->pstate == RUNNING)
		ultimateyeet("Boi why is you running in yield");

	/* TODO */
}
