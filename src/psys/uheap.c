#include "dat.h"
#include "fns.h"

#include <hsys.h>
#include <msys.h>
#include <psys.h>

unsigned long
growby(unsigned long amount)
{
	unsigned long oldsz, newsz;

	if(amount == 0) return currentproc->memsize;

	acquire(&currentproc->lock);
	oldsz = currentproc->memsize;
	newsz = currentproc->memsize + amount;
	mkuserpages(currentproc->upgtbl, oldsz, newsz, MEMTYPE_DATA);

	currentproc->memsize = newsz;
	release(&currentproc->lock);

	return currentproc->memsize;
}
