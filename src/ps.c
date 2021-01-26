/* Process server */

struct psproc{
	unsigned long pid;
	char *name;

	__attribute__((section(".text.ps"))) void
	psmain(void)
	{
		int i;

		i = 0;
		for(;;) i++;
	}
