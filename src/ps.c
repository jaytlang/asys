/* Process server */

extern unsigned long dosyscall(unsigned long num, unsigned long one,
                               unsigned long two, unsigned long three,
                               unsigned long four, unsigned long five);

#define TEST    0
#define SENDREC 1

__attribute__((section(".text.ps"))) void
psmain(void)
{
	int i;

	i = dosyscall(TEST, 0, 0, 0, 0, 0);
	if(i != 0){
		for(;;)
			;
	}

	dosyscall(SENDREC, 0, 0, 555555, 0, 0);

	for(;;) i++;
}
