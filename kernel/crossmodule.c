#include "dat.h"
#include "fns.h"

#include <hsys.h>
#include <msys.h>

/* Shims for when functionality required
 * crosses kernel "module" borders.
 */
void
newproctotrapret(void)
{
	unsigned long addr;

	addr = UTRAPVEC + ((unsigned long)lluret - (unsigned long)llutrap);
	gotouser((void (*)(unsigned long *, void *))addr);
}
