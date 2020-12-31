#include <dsys.h>

#include "dat.h"
#include "fns.h"

__attribute__((aligned(16))) char kstack[4096];

int
main()
{
	uartinit();
	uartwrite("Hello there (:\n");
	return 0xdeadbeef;
}
