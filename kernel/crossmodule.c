#include "dat.h"
#include "fns.h"

#include <hsys.h>
#include <psys.h>

/* Shims for when functionality required
 * crosses kernel "module" borders.
 */
void
newproctotrapret(void)
{
	gotouser(lluret);
}
