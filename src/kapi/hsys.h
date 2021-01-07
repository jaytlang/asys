#ifndef INC_KAPI_HSYS
#define INC_KAPI_HSYS

/* Peripheral I/O */
void	devwrite(unsigned long address, unsigned int offset, char value);
char	devread(unsigned long address, unsigned int offset);

/* Spinlocks */
void	acquire(unsigned int *lock);
void	release(unsigned int *lock);

/* Death */
void	ultimateyeet(char *reason);

/* Paging enable */
void    installpgtbl(unsigned long *pgtbl);

/* Whomstdve am I? */
unsigned long   hartid(void);

/* Enable/disable interrupts */
#define INTRON 1L
#define INTROFF 0L

void    togglesintr(unsigned long on);

/* Addresses of hardware devices used
 * for all sorts of various purposes.
 * To be removed/deprecated.
 */
#define UART_ADDRESS 0x10000000

#endif /* INC_KAPI_HSYS */
