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

#endif /* INC_KAPI_HSYS */
