#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <msys.h>
#include <psys.h>

void
utrap(unsigned long sstatus, unsigned long scause,
      void (*ret)(unsigned long *, void *))
{
	int devintrres;

	/* Prevent any further issues NOW by restoring stvec */
	setstvec(0);

	/* Check we're from usermode */
	if((sstatus & SSTATUS_SPPMASK) != 0)
		ultimateyeet("Entered utrap from kernel mode?");

	/* Ensure that interrupts are currently disabled */
	if((sstatus & SSTATUS_SIEMASK) != 0)
		ultimateyeet("Interrupts are still on, whomstdvent");

	/* Handle it as we normally would...no syscalls yet but that
	 * check would go here. We would also turn on interrupts
	 */
	devintrres = handledevintr(scause);

	/* If this is a timer interrupt, yield */
	if(devintrres != DEVINTR_TIMER)
		uartwrite(
		    "Unknown interrupt from usermode caught and discarded\n");
	else{
		suspend();
	}

	gotouser(ret);
}

void
gotouser(void (*ret)(unsigned long *, void *))
{
	unsigned long *pgtbl;

	/* Disable interrupts in preparation for the yeet */
	togglesintr(INTROFF);

	/* get the trap frame and pgtbl from psys */
	pgtbl = exportupgtbl();

	/* bye! */
	ret(pgtbl, (void *)(UTRAPFRM));
}
