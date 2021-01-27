/* Process server
 * Programmed in early userland code-style
 * to enable everything to work properly
 * without a dedicated binary
 */
#include "dat.h"

__attribute__((section(".text.ps"))) void
psmain(void)
{
	int i;

	i = pssyscall(SYS_TEST, 0, 0, 0, 0, 0);
	if(i != 0){
		for(;;)
			;
	}

	pssyscall(SYS_SENDREC, 0, 0, 555555, 0, 0);

	for(;;) i++;
}
