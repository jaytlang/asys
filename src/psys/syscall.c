#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <psys.h>

unsigned long
test(void)
{
	uartwrite("Hello this is a test syscall\n");
	return 0;
}

void
syscall(void)
{
	unsigned long result;

	/* We're done mutating the process
	 * trapframe so activate interrupts after
	 * lock release...
	 */
	togglesintr(INTRON);

	/* Examine the trapframe without touching
	 * it now, and figure out the syscall cause
	 */
	if(currentproc->trapframe->a0 == SYS_TEST) result = test();
	else{
		uartwrite("Unknown syscall: ");
		uartwritenum(currentproc->trapframe->a0);
		uartwrite("\n");
		result = -1;
	}

	acquire(&currentproc->lock);
	currentproc->trapframe->a0 = result;
	currentproc->trapframe->epc += 4;
	release(&currentproc->lock);

	return;
}
