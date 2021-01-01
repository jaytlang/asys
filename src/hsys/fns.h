#ifndef INC_HSYS_LOCK
#define INC_HSYS_LOCK

/* Assembly routines in l.S: atomic lock
 * acquisition / swap operations
 */
extern void	llacquire(unsigned int *lock);
extern void	llrelease(unsigned int *lock);

#endif /* INC_HSYS_LOCK */
