#include <hsys.h>
#include <dsys.h>

#include "uart.h"

/* Back when men were men, and wrote their own device drivers... */

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

char
uartreadc(void)
{
	if(devread(UART_ADDRESS, UART_OFFSET_LSR) == 0)
		return 0;
	else return devread(UART_ADDRESS, UART_OFFSET_DATA);
}

void uartwrite(char *c)
{
	while(*c) devwrite(UART_ADDRESS, UART_OFFSET_DATA, *c++);
}
