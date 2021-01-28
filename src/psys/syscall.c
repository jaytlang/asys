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

unsigned long
parg(unsigned int num)
{
	switch(num){
	case 1: return currentproc->trapframe->a1; break;
	case 2: return currentproc->trapframe->a2; break;
	case 3: return currentproc->trapframe->a3; break;
	case 4: return currentproc->trapframe->a4; break;
	case 5: return currentproc->trapframe->a5; break;
	default:
		ultimateyeet("bro you know better than this, 5 args/syscall");
		break;
	}

	/* never reached */
	return 0;
}

void
syscall(void)
{
	/* Note: syscall interface utilizes positive
	 * non-zero return values to indicate an error.
	 * The in-kernel has usually used negative numbers,
	 * but I see this slowly changing since `unsigned long`
	 * is more conventional for my code thus far
	 */
	unsigned long result;
	unsigned long callno;

	/* Activate interrupts... */
	togglesintr(INTRON);

	/* Examine the trapframe without touching
	 * it now, and figure out the syscall cause
	 */
	callno = currentproc->trapframe->a0;

	if(callno == SYS_TEST) result = test();
	else if(callno == SYS_SENDREC)
		result = sendrec(parg(1), parg(2));
	else if(callno == SYS_GROWBY)
		result = growby(parg(1));
	else{
		uartwrite("Unknown syscall: ");
		uartwritenum(currentproc->trapframe->a0);
		uartwrite("\n");
		result = 1;
	}

	acquire(&currentproc->lock);
	currentproc->trapframe->a0 = result;
	currentproc->trapframe->epc += 4;
	release(&currentproc->lock);

	return;
}
