#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>

/* OK so basically. This is a property specific
 * to a given kernel context (including the global
 * context). When we acquire, we turn off interrupts
 * to avoid issues with spinlocks (see the commit log,
 * i think i explain it there). eventually, when we
 * release everything, we flip interrupts back to
 * how they were before the first acquire.
 *
 * Because this is specific to a given kernel context,
 * we need to accurately update it when we are switching
 * contexts. This is especially pertinent bc we hold the
 * lock on the process when we jump to the scheduler, to
 * prevent anything weird from happening and to match state
 * with how we entered: the scheduler acquires the process lock
 * to do stuff before it enters and never releases.
 *
 * When we perform a context switch, we can /get/
 * this and save it in a variable, then when we return pop
 * it off and restore it here.
 */
unsigned long oldintrstate = INTROFF;
unsigned long kernelstvec = 0;

unsigned long
getoldintrstate(void)
{
	return oldintrstate;
}

void
setoldintrstate(unsigned long newstate)
{
	oldintrstate = newstate;
}

/* Set stvec, designating where kernel interrupts should go */
void
setstvec(unsigned long destination)
{
	if(destination != 0) kernelstvec = destination;
	else if(kernelstvec == 0)
		ultimateyeet("Unknown default kernel interrupt handler");

	llsetstvec(kernelstvec);
}

int
handledevintr(unsigned long scause)
{
	if((scause & SCAUSE_INTR) == 0){
		ultimateyeet("Called devintr() when there was no interrupt");
		return -1;
	}

	if((scause & SCAUSE_EXCODEMASK) == EXCODE_EXTERNINTR)
		/* External interrupt via the PLIC.
		 * We don't know how to handle this yet
		 */
		return -1;

	else if((scause & SCAUSE_EXCODEMASK) == EXCODE_MMODESWINTR){
		/* Software interrupt from machine mode - timer
		 * Clear the software interrupt bit in sip once
		 * we've figured this one out
		 */
		uartwrite("Yo, we got a timer interrupt!\n");
		llclearsip();
		return DEVINTR_TIMER;
	}

	else{
		ultimateyeet("devintr(): What's this interrupt? IDK!");
		return -1;
	}
}

void
ktrap(unsigned long sepc, unsigned long sstatus, unsigned long scause)
{
	int result;

	/* Ensure we came from supervisor mode */
	if((sstatus & SSTATUS_SPPMASK) == 0)
		ultimateyeet("Entered ktrap from user mode?");

	/* Ensure interrupts are disabled, i.e. this is
	 * truly a trap context and we're good to do what we
	 * need to do
	 */
	if((sstatus & SSTATUS_SIEMASK) != 0)
		ultimateyeet("Interrupts are still on, whomstdvent");
	/* Process the interrupt */
	result = handledevintr(scause);
	if(result == -1) uartwrite("Unknown interrupt caught and discarded\n");

	/* Return to previous task, setting the PC back to what
	 * it should be and auto-getting machine mode with the sret
	 * instruction
	 */
	llsetsepc(sepc);
	llsetsstatus(sstatus);
}

void
togglesintr(unsigned long on)
{
	if(on > 0) llsieon();
	else
		llsieoff();
}

unsigned long
getsintr(void)
{
	return llgetsie();
}
