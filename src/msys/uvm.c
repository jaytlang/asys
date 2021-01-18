#include "dat.h"
#include "fns.h"

#include <hsys.h>
#include <lsys.h>
#include <msys.h>

unsigned long *
mkupgtbl(char *trapframe)
{
	unsigned long *newpgtbl;

	newpgtbl = allocpage();
	if(!newpgtbl) ultimateyeet("Out of memory!");
	memset(newpgtbl, 0, PAGESIZE);

	/* Initialize the user page table with the provided
	 * trap frame...wtf is modularity
	 */
	map(newpgtbl, (char *)UTRAPVEC, utrap, PTER | PTEX);
	map(newpgtbl, (char *)UTRAPFRM, trapframe, PTER | PTEW);

	return newpgtbl;
}
