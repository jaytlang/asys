#include <hsys.h>

#include "fns.h"

void
installpgtbl(unsigned long *pgtbl)
{
	unsigned long ppn, mode;
	/* We need to set the mode field properly: 8 for
	 * the SV39 address scheme that msys sets up
	 */
	ppn = (unsigned long)pgtbl >> 12;
	mode = ((unsigned long)8 << 60);

	llsetsatp(mode | ppn);
}
