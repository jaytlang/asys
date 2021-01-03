#include <msys.h>
#include <lsys.h>
#include <dsys.h>

#include "dat.h"

struct freelist *basenode;

void
initpagealloc(void)
{
	char *p;

	/* ekernel isn't necessarily page aligned */
	p = (char *)(((unsigned long)ekernel + PAGESIZE - 1) & ~(PAGESIZE - 1));
	uartwrite("Indexing system memory\n");
	for(; p + PAGESIZE < (char *)MEMORY_TOP; p += PAGESIZE){
		freepage((void *)p);
	}
}
void
freepage(void *page)
{
	struct freelist *thisnode;

	if((unsigned long)page % PAGESIZE != 0)
		ultimateyeet("Tried to free off a page boundary\n");

	else if((char *)page < ekernel)
		ultimateyeet("Can't free part of the kernel you dummy\n");

	else if((unsigned long)page >= MEMORY_TOP)
		ultimateyeet("Can't free above the top of physical memory\n");

	memset(page, 0, PAGESIZE);
	thisnode = (struct freelist *)page;
	thisnode->next = basenode;
	basenode = thisnode;
}

void *
allocpage(void)
{
	struct freelist *page;

	page = basenode;
	if(basenode) basenode = basenode->next;

	memset((char *)page, 0, PAGESIZE);
	return (void *)page;
}
