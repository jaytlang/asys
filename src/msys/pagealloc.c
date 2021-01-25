#include "dat.h"
#include "fns.h"

#include <dsys.h>
#include <hsys.h>
#include <lsys.h>
#include <msys.h>

struct freelist *basenode;
unsigned int pglock = 0;

void
initpagealloc(void)
{
	char *p;

	/* ekernel isn't necessarily page aligned. Round up */
	p = (char *)roundup((unsigned long)ekernel, PAGESIZE);

	/* assume no locking needed yet */
	basenode = NULL;
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

	acquire(&pglock);
	thisnode->next = basenode;
	basenode = thisnode;
	release(&pglock);
}

void *
allocpage(void)
{
	struct freelist *page;

	acquire(&pglock);
	if(basenode){
		page = basenode;
		basenode = basenode->next;
		release(&pglock);

		memset((char *)page, 0, PAGESIZE);
		return (void *)page;
	}else{
		release(&pglock);
		return NULL;
	}
}
