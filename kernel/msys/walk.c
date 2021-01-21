#include "dat.h"
#include "fns.h"

#include <hsys.h>
#include <lsys.h>
#include <msys.h>

unsigned long *
descendonce(unsigned long *pgtbl, char *va, unsigned int level)
{
	unsigned long *pte;

	/* This really shouldn't happen */
	if((unsigned long)va >= MAXVA) ultimateyeet("descend: bad va");
	if(level > 2) ultimateyeet("descend: bad level");

	/* This is theoretically fine */
	if(!pgtbl) return NULL;

	/* Okay. Let's get the PTE out for our level,
	 * making sure it's okay before we deref. It's
	 * possible everything is okay here but the
	 * pgtbl in question is yet unmapped
	 */
	pte = &pgtbl[indexfromva(va, level)];
	if(!pte) return NULL;
	else
		return (unsigned long *)physviapte(*pte);
}

unsigned long *
pteforva(unsigned long *pgtbl, char *va)
{
	int level;
	unsigned long *nextpgtbl;

	if(!pgtbl) ultimateyeet("translate: bad pgtbl");
	if((unsigned long)va >= MAXVA) ultimateyeet("translate: bad va");

	nextpgtbl = pgtbl;

	for(level = 2; level > 0; level--){
		nextpgtbl = descendonce(nextpgtbl, va, level);
		if(!nextpgtbl) return NULL; /* doesn't exist */
	}

	return &nextpgtbl[indexfromva(va, 0)];
}

unsigned long *
translateva(unsigned long *pgtbl, char *va)
{
	unsigned long *pte;

	pte = pteforva(pgtbl, va);
	return (unsigned long *)physviapte(*pte);
}
