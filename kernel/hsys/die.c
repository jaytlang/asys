#include "fns.h"

#include <dsys.h>
#include <lsys.h>

/* Big and ultimate sad */
void
ultimateyeet(char *reason)
{
	uartwrite("I AM DED\n");
	uartwrite(reason);
	llwfi();
}
