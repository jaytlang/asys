/* Process server */

extern unsigned long testsyscall(void);

__attribute__((section(".text.ps"))) void
psmain(void)
{
	int i;

	i = testsyscall();
	for(;;) i++;
}
