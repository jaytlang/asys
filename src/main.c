#include <dsys.h>

#include "dat.h"
#include "fns.h"

__attribute__((aligned(16))) char kstack[4096];

int
main()
{
	char thischar;

	uartinit();
	uartwrite("Hello there! Type what you want. (:\n");

	for(;;){
		thischar = uartreadc();	
		uartwrite(&thischar);
	}
	return 0xdeadbeef;
}
