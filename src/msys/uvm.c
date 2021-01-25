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
	map(newpgtbl, (char *)UTRAPVEC, utrapaddr, PTER | PTEX);
	map(newpgtbl, (char *)UTRAPFRM, trapframe, PTER | PTEW);

	return newpgtbl;
}

void
mkuserpages(unsigned long *pgtbl, unsigned long oldsz, unsigned long newsz,
            int mtype)
{
	unsigned long trueold, truenew, i;
	unsigned long *page;
	int perm;

	/* oldsize needs to be aligned to the page boundary
	 * if we stick with this pattern, we won't need to
	 * worry about aligning truenew since the process can think
	 * it only has part of a page.
	 */
	trueold = roundup(oldsz, PAGESIZE);
	truenew = newsz;

	/* set permissions based upon mtype */
	if(mtype == MEMTYPE_DATA) perm = PTER | PTEW | PTEU;
	else if(mtype == MEMTYPE_CODE)
		perm = PTER | PTEX | PTEU;
	else if(mtype == MEMTYPE_GUARD)
		perm = PTER | PTEW;
	else{
		ultimateyeet("moreuserpages: bad mtype");
		return;
	}

	for(i = trueold; i < truenew; i += PAGESIZE){
		page = allocpage();
		if(!page) ultimateyeet("Out of memory!");
		memset(page, 0, PAGESIZE);

		map(pgtbl, (char *)i, (char *)page, perm);
	}
}
