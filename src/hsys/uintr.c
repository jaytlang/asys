#include <dsys.h>
#include <hsys.h>

/*
void
utrap(unsigned long sepc, unsigned long sstatus, unsigned long scause)
{
        int devintrres;

        / Check we're from usermode /
        if((sstatus & SSTATUS_SPPMASK) != 0)
                ultimateyeet("Entered utrap from kernel mode?");

        / Ensure that interrupts are currently disabled /
        if((sstatus & SSTATUS_SIEMASK) != 0)
                ultimateyeet("Interrupts are still on, whomstdvent");

        /. Handle it as we normally would...no syscalls yet but that
         . check would go here. We would also turn on interrupts
         ./
        devintrres = handledevintr(scause);
        if(result < 0)
                uartwrite("Unknown interrupt caught and discarded");

        llsetsepc(sepc);
        llsetsstatus(sstatus);

        / TODO /
}
*/
