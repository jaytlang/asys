#include "fns.h"

#include <hsys.h>

unsigned long
hartid(void)
{
	return llhartid();
}