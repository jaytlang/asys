#include <dsys.h>
#include <msys.h>

#include "dat.h"

void
printpageallocstate(void)
{
	uartwrite("PAGE ALLOCATOR STATE:\n");
	if(!basenode){
		uartwrite("\tNo page table set up yet.\n");
		return;
	}

	uartwrite("\tekernel: "); uartwritenum((unsigned long)ekernel);
	uartwrite("\n\tMEMORY_TOP: "); uartwritenum(MEMORY_TOP);

	/*
	for(thisnode = basenode; thisnode->next; thisnode = thisnode->next){
		uartwrite("\t\tFree page at: ");
		uartwritenum((unsigned long)thisnode);
		uartwrite("\n"):
	}
	*/
}


