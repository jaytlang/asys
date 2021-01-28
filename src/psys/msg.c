#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <lsys.h>
#include <msys.h>
#include <psys.h>

/* IMPORTANT: THIS IMPLEMENTATION DOESN'T FULLY WORK YET
 * message sizes of over 4096 bytes will crash the kernel
 * this is because we don't have an allocator that's capable
 * of allocating more memory than that of a single page.
 * this should change down the road, since it's not hard to
 * map lots of memory into kpgtbl and get rid of it later.
 */
unsigned long
sendrec(unsigned long dstcode, unsigned long msg)
{
	unsigned long result;

	uartwrite("Unknown message destination for msg: ");
	uartwritenum(msg);
	uartwrite("\n");
	result = dstcode;

	return result;
}
