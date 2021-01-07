#include <dsys.h>
#include <msys.h>
#include <hsys.h>

#include "dat.h"
#include "fns.h"

/* Kernel stack for the first hart */
__attribute__((aligned(16))) char kstack[4096];

int
main()
{
	unsigned long *initialpgtbl;

	uartinit();
	uartwrite("asyskrn.exe version 0.1\n");
	uartwrite("\nMapping system memory...\n");
	initialpgtbl = setupkvm();

	uartwrite("Enabling paging.\n");
	installpgtbl(initialpgtbl);
	uartwrite("Paging is ON! HELLO WORLD!\n");

	uartwrite("For your information, I am hart ");
	uartwritenum(hartid());
	uartwrite("\n");

	uartwrite("Enabling kernel preemption...");
	togglesintr(INTRON);
	uartwrite("done\n");

	for(;;);
	return 0xdeadbeef;
}
