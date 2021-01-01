#ifndef INC_DSYS_UART
#define INC_DSYS_UART

#define UART_ADDRESS 0x10000000
#define UART_OFFSET_LCR 0x3
#define UART_OFFSET_FCR 0x2
#define UART_OFFSET_IER 0x1
#define UART_OFFSET_LSR 0x5
#define UART_OFFSET_DATA 0x0

extern unsigned int uartlock;

#endif /* INC_DSYS_UART */
