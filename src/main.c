#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <isys.h>
#include <msys.h>
#include <psys.h>

/* Kernel stack for the first hart */
__attribute__((aligned(16))) char kstack[4096];

/* Shims for when functionality required
 * crosses kernel "module" borders.
 */
void
newproctotrapret(void)
{
	unsigned long addr;

	addr = UTRAPVEC + ((unsigned long)lluret - (unsigned long)llutrap);
	gotouser((void (*)(unsigned long *, void *))addr);
}

/* Kernel entrypoint */
int
main()
{
	uartinit();
	uartwrite("asyskrn.exe (jayos) version 0.0.1\n");

	uartwrite("Registering trap vector...");
	registerutrap(llutrap);
	uartwrite("done\n");

	uartwrite("Registering kernel stack...");
	registerkstack(kstack);
	uartwrite("done\n");

	uartwrite("Mapping system memory...\n");
	setupkvm();

	uartwrite("Installing kernel page table...");
	installpgtbl(kpgtbl);
	uartwrite("done\n");

	uartwrite("Verify hartid: ");
	uartwritenum(hartid());
	uartwrite("...done\n");

	uartwrite("Enabling kernel preemption...");
	setstvec((unsigned long)llstrap);
	togglesintr(INTRON);
	uartwrite("done\n");

	uartwrite("Init plist with kernel stack...");
	procinitvia(newproctotrapret);
	uartwrite("done\n");

	uartwrite("Ensure no locks currently held: ");
	uartwritenum(locksheld());
	uartwrite("...done\n");

	uartwrite("Reading initramfs...\n");
	initramdisk();
	uartwrite("...done\n");

	uartwrite("\nKernel initialization complete.\n\n");
	for(;;)
		;
	scheduler();

	return 0xdeadbeef;
}
