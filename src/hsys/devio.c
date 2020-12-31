#include <hsys.h>

void
devwrite(unsigned long address, unsigned int offset, char value)
{
	volatile char *reg = (char *)address;
	*(reg + offset) = value;
}

char
devread(unsigned long address, unsigned int offset)
{
	volatile char *reg = (char *)address;
	return *(reg + offset);
}
