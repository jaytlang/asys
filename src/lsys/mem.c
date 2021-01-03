#include <lsys.h>

void *
memset(void *region, char byte, unsigned int count)
{
	char *byteptr;
	unsigned int i;

	byteptr = (char *)region;
	for(i = 0; i < count; i++)
		byteptr[i] = byte;

	/* why? */
	return region;
}
