#include "dat.h"
#include "fns.h"

__attribute__((aligned(16))) char kstack[4096];

int
main()
{
	return 0xdeadbeef;
}
