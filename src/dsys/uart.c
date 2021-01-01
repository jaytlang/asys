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

/* Unequivocally useless and absolutely horrible: this should
 * be a sleep lock. At this rate I'm gonna take it out.
 */
char
uartreadc(void)
{
	char result;

	acquire(&uartlock);
	while(devread(UART_ADDRESS, UART_OFFSET_LSR) == 0);

	result = devread(UART_ADDRESS, UART_OFFSET_DATA);
	release(&uartlock);
	return result;
}

void uartwrite(char *c)
{
	acquire(&uartlock);
	while(*c) devwrite(UART_ADDRESS, UART_OFFSET_DATA, *c++);
	release(&uartlock);
}
