/* Process server
 * Programmed in early userland code-style
 * to enable everything to work properly
 * without a dedicated binary
 */
#include "dat.h"

PSFN void
psmain(void)
{

	/* hello we exist (: */
	pssyscall(SYS_TEST, 0, 0, 0, 0, 0);
	for(;;)
		;
}
