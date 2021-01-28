#include "dat.h"

#include <dsys.h>
#include <isys.h>

struct ent *superblock;

void
initramdisk(void)
{
	superblock = (struct ent *)_binary_initrd_dat_start;
	uartwrite("Magic number is: ");
	uartwritenum(superblock->magic);
	uartwrite("\n");
}
