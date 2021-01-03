#include <dsys.h>
#include <msys.h>

#include "dat.h"
#include "fns.h"

__attribute__((aligned(16))) char kstack[4096];

int main()
{
	uartinit();
	uartwrite("asyskrn.exe version 0.1\n");
	uartwrite("\nInitializing the page allocator\n");


	initpagealloc();
	printpageallocstate();
	return 0xdeadbeef;
}
