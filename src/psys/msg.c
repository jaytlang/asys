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
sendrec(char *msgva, char *resbuf, unsigned long dstcode, unsigned long len)
{
	char *pa;
	char *rawresult;
	unsigned long retval;

	if(len > PAGESIZE)
		ultimateyeet(
		    "PAGESIZE byte + messages are currently unsupported");

	/* Copy the message into kernelspace */
	pa = allocpage();
	memset(pa, 0, PAGESIZE);

	if(copyfrompgtbl(currentproc->upgtbl, pa, msgva, len) < 0)
		ultimateyeet("Failed to copyin message to kernel");

	/* pa now contains message. send it to who matters...unless it's
	 * a kernel message in which case handle it
	 */
	if(dstcode == DST_KERNEL){
		uartwrite("Received message to the kernel:");
		uartwrite(pa);
		uartwrite("\n");

		/* handle the message by making the proper invocation */
		freepage(pa);
		rawresult = "";
		retval = 0;
	}else{
		uartwrite("Unknown message destination, discarding.\n");
		freepage(pa);
		rawresult = "no";
		retval = 1;
	}

	/* Return to userspace after telling the process we have
	 * literally no idea what's going on at all send help
	 */
	if(copytopgtbl(currentproc->upgtbl, resbuf, rawresult,
	               strlen(rawresult) + 1) < 0)
		ultimateyeet("Failed to copyout response to user");

	return retval;
}
