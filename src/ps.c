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
	char sendbuf[12];
	char recvbuf[12];

	i = dosyscall(TEST, 0, 0, 0, 0, 0);
	if(i != 0){
		for(;;)
			;
	}

	sendbuf[0] = 'h';
	sendbuf[1] = 'i';
	sendbuf[2] = '!';
	sendbuf[3] = '!';
	sendbuf[4] = '\0';

	dosyscall(SENDREC, (unsigned long)sendbuf, (unsigned long)recvbuf, 0, 5,
	          0);

	for(;;) i++;
}
