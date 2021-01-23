#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <psys.h>

void
syscall(void)
{
	uartwrite("acked system call\n");
	acquire(&currentproc->lock);
	currentproc->trapframe->epc += 4;
	release(&currentproc->lock);
}
