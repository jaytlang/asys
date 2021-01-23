#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <psys.h>

void
syscall(void)
{
	acquire(&currentproc->lock);
	uartwrite("acked system call\n");
	currentproc->trapframe->epc += 4;
	release(&currentproc->lock);
}
