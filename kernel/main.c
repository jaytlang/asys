#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <msys.h>
#include <psys.h>

/* Kernel stack for the first hart */
__attribute__((aligned(16))) char kstack[4096];

int
main()
{
	uartinit();
	uartwrite("asyskrn.exe version 0.1\n");

	uartwrite("\nRegistering trap vector...");
	registerutrap(llutrap);
	uartwrite("done\n");

	uartwrite("Mapping system memory...\n");
	setupkvm();

	uartwrite("Enabling paging.\n");
	installpgtbl(kpgtbl);
	uartwrite("Paging is ON! HELLO WORLD!\n");

	uartwrite("For your information, I am hart ");
	uartwritenum(hartid());
	uartwrite("\n");

	uartwrite("Enabling kernel preemption...");
	togglesintr(INTRON);
	uartwrite("done\n");

	uartwrite("Init plist with kernel stack...");
	procinitvia(newproctotrapret);
	uartwrite("done\n");

	uartwrite("Locks currently held: ");
	uartwritenum(locksheld());
	uartwrite("\n");

	for(;;)
		;
	return 0xdeadbeef;
}
