#include <hsys.h>

#include "fns.h"

void
acquire(unsigned int *lock)
{
	/* Assembly shim: this directly implements
	 * a spinlock acquisition
	 */
	llacquire(lock);
}

void
release(unsigned int *lock)
{
	llrelease(lock);
}
