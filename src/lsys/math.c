#include <lsys.h>

unsigned long
roundup(unsigned long input, unsigned long roundto)
{
	return (input + roundto + 1) & ~(roundto - 1);
}

unsigned long
rounddown(unsigned long input, unsigned long roundto)
{
	return input & ~(roundto - 1);
}
