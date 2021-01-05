#ifndef INC_HSYS_LOCK
#define INC_HSYS_LOCK

/* Assembly routines in l.S: atomic lock
 * acquisition / swap operations, panic
 */
extern void	llacquire(unsigned int *lock);
extern void	llrelease(unsigned int *lock);
extern void	llwfi(void);
extern void	llsetsatp(unsigned long satp);

/* mhartid, aka mv a0, tp because who
 * needs thread local storage? NOT ME
 */
 extern unsigned long llhartid(void);

#endif /* INC_HSYS_LOCK */
