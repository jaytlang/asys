#include <msys.h>
#include <hsys.h>
#include <lsys.h>
#include <dsys.h>

#include "dat.h"
#include "fns.h"

unsigned long *kpgtbl;
char *utrap;

void
registerutrap(char *addr)
{
	utrap = addr;
}

/* Do a page table! HYPE 1000 */
unsigned long *
setupkvm(void)
{
	char *this;

	initpagealloc();

	kpgtbl = (unsigned long *)allocpage();
	memset(kpgtbl, 0, PAGESIZE);

	/* Devices we need go into our address
	 * space. Eventually this number is gonna
	 * drop to zero, but for now the UART driver
	 * lives in the kernel, and we don't need a
	 * primitive for users to request DMA to it
	 */
	uartwrite("\tMapping UART\n");
	map(kpgtbl, (char *)UART_ADDRESS, (char *)UART_ADDRESS, PTER | PTEW);

	/* Kernel text, data. This covers the kstack too, so we're good. */
	uartwrite("\tMapping kernel text\n");
	for(this = (char *)KERNBASE; this < etext; this += PAGESIZE){
		map(kpgtbl, this, this, PTER | PTEX);
	}

	uartwrite("\tMapping kernel data\n");
	for(this = (char *)etext; (unsigned long)this < MEMORY_TOP;
	    this += PAGESIZE){

		map(kpgtbl, this, this, PTER | PTEW);
	}

	/* Finally, map the u->k trampoline in */
	map(kpgtbl, (char *)UTRAPVEC, utrap, PTER | PTEX);

	/* kpgtbl is ready to install */
	return kpgtbl;
}
