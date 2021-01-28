#ifndef INC_PSYS_DAT
#define INC_PSYS_DAT

struct kcontext{
	unsigned long ra;
	unsigned long sp;

	unsigned long s0;
	unsigned long s1;
	unsigned long s2;
	unsigned long s3;
	unsigned long s4;
	unsigned long s5;
	unsigned long s6;
	unsigned long s7;
	unsigned long s8;
	unsigned long s9;
	unsigned long s10;
	unsigned long s11;
};

extern struct kcontext *globalcontext;

struct trapframe{
	void (*stg2)(unsigned long, unsigned long,
	             void (*ret)(unsigned long *, void *));

	unsigned long ksatp;
	unsigned long ksp;

	unsigned long epc;
	unsigned long ra;
	unsigned long sp;
	unsigned long gp;
	unsigned long a0;
	unsigned long a1;
	unsigned long a2;
	unsigned long a3;
	unsigned long a4;
	unsigned long a5;
	unsigned long a6;
	unsigned long a7;
	unsigned long s0;
	unsigned long s1;
	unsigned long s2;
	unsigned long s3;
	unsigned long s4;
	unsigned long s5;
	unsigned long s6;
	unsigned long s7;
	unsigned long s8;
	unsigned long s9;
	unsigned long s10;
	unsigned long s11;
	unsigned long t0;
	unsigned long t1;
	unsigned long t2;
	unsigned long t3;
	unsigned long t4;
	unsigned long t5;
	unsigned long t6;
};

enum procstate{ RUNNING, RUNNABLE, SLEEPING };

#define NOCONDITION 0
#define PROCNAMESZ  20

struct proc{
	unsigned int lock;

	enum procstate pstate;
	unsigned long pid;

	char *name;

	unsigned long *upgtbl; /* Obviously a page but separate */
	unsigned long memsize;

	char *ksbase;
	struct kcontext pkcontext;   /* Inline */
	struct trapframe *trapframe; /* A page */

	struct proc *next;
};

/* System calls */
#define SYS_TEST   0
#define SYS_GROWBY 1

/* Message destination */
#define DST_KERNEL 0

extern struct proc *proclist;
extern struct proc *currentproc;
extern unsigned int proclistlock;

extern char *globalkstack;

#endif /* INC_PSYS_DAT */
