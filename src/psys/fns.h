#ifndef INC_PSYS_FNS
#define INC_PSYS_FNS

struct proc;

/* Utilities */
unsigned long newpid(void);

/* Internal route to hsys for
 * new processes to follow
 */
extern void (*tohsys)(void);

/* Internal scheduler entry */
void yield(void);

/* make a new process to begin with */
struct proc *mkproc(char *name);

/* send/receive messages */
unsigned long sendrec(char *msgva, char *resbuf, unsigned long dstcode,
                      unsigned long len);

#endif /* INC_PSYS_FNS */
