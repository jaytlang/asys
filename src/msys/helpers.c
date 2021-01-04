#include "dat.h"
#include "fns.h"

unsigned long
indexfromva(char *va, unsigned int level)
{
	return (((unsigned long)va >> VAOFFSETBITS
		        >> (VALEVELBITS * level))
			& 0x1ff);	
}

char *
physviapte(unsigned long pte)
{
	return (char *)(pte >> PTEFLAGBITS << VAOFFSETBITS);
}

unsigned long
pteviaphys(char *phys)
{
	return (unsigned long)phys >> VAOFFSETBITS << PTEFLAGBITS;
}
