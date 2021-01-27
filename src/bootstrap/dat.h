/* Bootstrap macros for ps/is to operate */

#ifndef INC_USER_BS
#define INC_USER_BS

/* Actual syscall stuff */
extern unsigned long pssyscall(unsigned long num, unsigned long one,
                               unsigned long two, unsigned long three,
                               unsigned long four, unsigned long five);

/* Syscall definitions */
#define SYS_TEST    0
#define SYS_SENDREC 1
#define SYS_GROWBY  2

/* sendrec destinations */

/* psproc permission bitmask */
#define PERM_SYS_TEST   1L << 0
#define PERM_SYS_GROWBY 1L << 1

/* ps: proc structure */
struct psproc{
	unsigned long permissions;
	unsigned long pid;
	struct psproc *next;
};

/* duh */
#define NULL ((void *)0)

#endif /* INC_USER_BS */
