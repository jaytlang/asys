#include <hsys.h>
#include <dsys.h>

#include "uart.h"

/* Back when men were men, and wrote their own device drivers... */
unsigned int uartlock = 0;

void
uartinit(void)
{
	/* Set word length to eight by enabling the bottom
	 * two bits of the LCR register. Then enable the FIFO
	 * and enable receive buffer interrupts
	 */
	devwrite(UART_ADDRESS, UART_OFFSET_LCR, 0x3);
	devwrite(UART_ADDRESS, UART_OFFSET_FCR, 0x1);
	devwrite(UART_ADDRESS, UART_OFFSET_IER, 0x1);
}

void
uartwrite(char *c)
{
	acquire(&uartlock);
	while(*c) devwrite(UART_ADDRESS, UART_OFFSET_DATA, *c++);
	release(&uartlock);
}

void
uartwritenum(unsigned long num)
{
	char buf[20];	/* max 64 bit number has 20 digits */
	unsigned int i, j;

	i = 0;

	while(num > 0 && i < 20){
		buf[i++] = num % 10 + '0';
		num /= 10;
	}
	acquire(&uartlock);
	for(j = i; j != 0; j--)
		devwrite(UART_ADDRESS, UART_OFFSET_DATA, buf[j-1]);
	release(&uartlock);
}
