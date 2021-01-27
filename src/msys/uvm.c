#include "dat.h"
#include "fns.h"

#include <dsys.h>
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

/* Copy data into the kernel...src/dst may not be page aligned */
int
copyfrompgtbl(unsigned long *pgtbl, char *dst, char *src, unsigned int sz)
{
	unsigned long thispg;
	char *thispa;
	unsigned int thiscnt, thisoffset;

	while(sz > 0){
		thispg = rounddown((unsigned long)src, PAGESIZE);
		thispa = (char *)translateva(pgtbl, (char *)thispg);

		if(thispa == NULL) return -1;

		thisoffset = (unsigned long)src - thispg;
		thiscnt = PAGESIZE - thisoffset;
		if(thiscnt > sz) thiscnt = sz;

		memcpy(dst, thispa + thisoffset, thiscnt);

		dst += thiscnt;
		src += thiscnt;
		sz -= thiscnt;
	}

	return 0;
}

/* Vice versa. This was confusing for me at first, but remember
 * that we AREN'T mapping kernel memory into userland. The user
 * has already allocated the right buffer for us, we're just mapping
 * through the right thing, paying attention to not-necessarily-
 * contiguous >PAGESIZE size buffers.
 */
int
copytopgtbl(unsigned long *pgtbl, char *dst, char *src, unsigned int sz)
{
	unsigned long thispg;
	char *thispa;
	unsigned int thiscnt, thisoffset;

	while(sz > 0){
		thispg = rounddown((unsigned long)dst, PAGESIZE);
		thispa = (char *)translateva(pgtbl, (char *)thispg);

		if(thispa == NULL) return -1;

		thisoffset = (unsigned long)dst - thispg;
		thiscnt = PAGESIZE - thisoffset;
		if(thiscnt > sz) thiscnt = sz;

		memcpy(thispa + thisoffset, src, thiscnt);

		dst += thiscnt;
		src += thiscnt;
		sz -= thiscnt;
	}

	return 0;
}
