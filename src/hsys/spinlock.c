#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>

unsigned long lockcnt = 0;

void
acquire(unsigned int *lock)
{
	if(lockcnt == 0) oldintrstate = getsintr();
	else if(getsintr() == INTRON)
		ultimateyeet("interrupts enabled with locks held");

	lockcnt += 1;
	togglesintr(INTROFF);
	llacquire(lock);
}

void
release(unsigned int *lock)
{
	if(lockcnt == 0) ultimateyeet("lockcnt is asymmetric somehow");
	if(getsintr() == INTRON)
		ultimateyeet("interrupts are on with locks held");

	lockcnt -= 1;
	llrelease(lock);
	if(lockcnt == 0) togglesintr(oldintrstate);
}

unsigned long
locksheld(void)
{
	return lockcnt;
}
