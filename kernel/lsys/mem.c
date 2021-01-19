#include <lsys.h>

void *
memset(void *region, char byte, unsigned int count)
{
	char *byteptr;
	unsigned int i;

	byteptr = (char *)region;
	for(i = 0; i < count; i++) byteptr[i] = byte;

	/* why? */
	return region;
}

void *
memcpy(void *dest, void *src, unsigned int count)
{
	char *s, *d;
	unsigned int i;

	s = src;
	d = dest;
	for(i = 0; i < count; i++) *d++ = *s++;

	return dest;
}
