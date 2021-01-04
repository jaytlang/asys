#include <msys.h>
#include <lsys.h>
#include <hsys.h>

#include "dat.h"
#include "fns.h"

void
map(unsigned long *pgtbl, char *va, char *pa, int perm)
{
	/* walk, allocating as needed.
	 * pgtbl might be new, that's fine.
	 * same for the va. descend thrice.
	 */
	unsigned long *thispgtbl, *nextpgtbl, *pte;
	int level;

	thispgtbl = pgtbl;
	for(level = 2; level > 0; level--){
		nextpgtbl = descendonce(thispgtbl, va, level);	
		if(!nextpgtbl){
			/* Make a new pgtbl */
			nextpgtbl = (unsigned long *)allocpage();
			if(!nextpgtbl)
				ultimateyeet("Out of memory!");
			memset(nextpgtbl, 0, PAGESIZE);

			/* Point at it from the last one */
			pte = &thispgtbl[indexfromva(va, level)];
			*pte = pteviaphys((char *)nextpgtbl) | PTEV;
		}
		thispgtbl = nextpgtbl;
	}

	/* We have the third page table. Do the blind dereference
	 * and check for a double mapping. These lines are probably
	 * why the OS shouldn't be written in Rust...
	 */
	pte = &thispgtbl[indexfromva(va, 0)];
	if(*pte & PTEV)
		ultimateyeet("map: tried to double map VA");

	/* Fill out the clear PTE */
	*pte = pteviaphys(pa) | perm | PTEV;
}
