#include <lsys.h>
#include <hsys.h>
#include <msys.h>

#include "dat.h"
#include "fns.h"

unsigned long *
mkupgtbl(char *trapvec)
{
	unsigned long *newpgtbl;

	newpgtbl = allocpage();
	if(!newpgtbl)
		ultimateyeet("Out of memory!");
	memset(newpgtbl, 0, PAGESIZE);

	/* Initialize the user page table with the provided
	 * trap vector...wtf is modularity
	 */
	map(newpgtbl, (char *)UTRAPVEC, utrap, PTER | PTEX);	
	map(newpgtbl, (char *)UTRAPFRM, trapvec, PTER | PTEW);

	return newpgtbl;
}

