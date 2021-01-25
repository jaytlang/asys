#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <lsys.h>

/* Big and ultimate sad */
void
ultimateyeet(char *reason)
{
	uartwrite("\n=================\n");
	uartwrite("I AM DED\n");
	uartwrite(reason);
	uartwrite("\n");

	togglesintr(INTROFF);
	llwfi();
}
