#include <hsys.h>
#include <dsys.h>

#include "dat.h"
#include "fns.h"

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
        return 0;
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
    if(result == -1)
        uartwrite("Unknown interrupt caught and discarded\n");
    
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
    else llsieoff();
}