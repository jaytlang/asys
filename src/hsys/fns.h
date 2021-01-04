#ifndef INC_HSYS_LOCK
#define INC_HSYS_LOCK

/* Assembly routines in l.S: atomic lock
 * acquisition / swap operations, panic
 */
extern void	llacquire(unsigned int *lock);
extern void	llrelease(unsigned int *lock);
extern void	llwfi(void);
extern void	llsetsatp(unsigned long satp);

#endif /* INC_HSYS_LOCK */
