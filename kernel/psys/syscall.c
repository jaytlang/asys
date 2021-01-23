#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <psys.h>

void
syscall(void)
{
	uartwrite("acked system call\n");
	currentproc->trapframe->epc += 4;
}
