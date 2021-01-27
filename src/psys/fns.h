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
unsigned long sendrec(unsigned long dstcode, unsigned long seqnum,
                      unsigned long msg);

#endif /* INC_PSYS_FNS */
