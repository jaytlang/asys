#ifndef INC_KAPI_HSYS
#define INC_KAPI_HSYS

/* Peripheral I/O */
void devwrite(unsigned long address, unsigned int offset, char value);
char devread(unsigned long address, unsigned int offset);

/* Spinlocks */
void acquire(unsigned int *lock);
void release(unsigned int *lock);
unsigned long locksheld(void);

/* Death */
void ultimateyeet(char *reason);

/* Paging enable */
void installpgtbl(unsigned long *pgtbl);

/* Target interrupts */
void setstvec(unsigned long destination);

/* Whomstdve am I? */
unsigned long hartid(void);

/* Enable/disable interrupts */
#define INTRON  1L
#define INTROFF 0L

void togglesintr(unsigned long on);
unsigned long getsintr(void);

/* Kernel threads */
unsigned long getoldintrstate(void);
void setoldintrstate(unsigned long newstate);
void llcontextswitch(void *old, void *new);

/* Addresses of hardware devices used
 * for all sorts of various purposes.
 * To be removed/deprecated.
 */
#define UART_ADDRESS 0x10000000

/* User trap handler: pedantry warning */
void utrap(unsigned long sstatus, unsigned long scause,
           void (*ret)(unsigned long *, void *));
void gotouser(void (*ret)(unsigned long *, void *));

#endif /* INC_KAPI_HSYS */
