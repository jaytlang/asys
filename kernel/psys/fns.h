#ifndef INC_PSYS_FNS
#define INC_PSYS_FNS

/* Utilities */
unsigned long newpid(void);

/* Internal route to hsys for
 * new processes to follow
 */
extern void (*tohsys)(void);

#endif /* INC_PSYS_FNS */
