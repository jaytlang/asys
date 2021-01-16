#include <hsys.h>

#include "dat.h"
#include "fns.h"

unsigned long intrct = 0;
unsigned long oldintrstate = INTROFF;

void
acquire(unsigned int *lock)
{
	if(intrct == 0) oldintrstate = getsintr();
	else if(getsintr() == INTRON)
		ultimateyeet("interrupts enabled with locks held");

	intrct += 1;
	togglesintr(INTROFF);
	llacquire(lock);
}

void
release(unsigned int *lock)
{
	if(intrct == 0)
		ultimateyeet("intrct is asymmetric somehow");
	if(getsintr() == INTRON)
		ultimateyeet("interrupts are on with locks held");

	intrct -= 1;
	llrelease(lock);
	if(intrct == 0) togglesintr(oldintrstate);
}
