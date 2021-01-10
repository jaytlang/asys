#ifndef INC_PSYS_DAT
#define INC_PSYS_DAT

struct kcontext{
	unsigned long ra;

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

extern struct kcontext globalcontext;

struct trapframe{
	unsigned long kpgtbl;
	unsigned long stg2;

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


enum procstate{
	RUNNING,
	RUNNABLE,
	SLEEPING
};

#define MSGBUFSZ 4096
#define NOCONDITION 0

struct proc{
	unsigned int lock;

	enum procstate pstate;

	char *msgbuf;		/* One page */
	unsigned long in;
	unsigned long out;
	unsigned long msgcondition;

	unsigned int killswitch;
	unsigned long pid;

	unsigned long *upgtbl;	/* Obviously a page but separate */
	unsigned long memsize;

	struct kcontext pkcontext;	/* Inline */
	struct trapframe *trapframe;	/* A page */

	struct proc *next;
};

extern struct proc *proclist;
extern struct proc *currentproc;

extern char *globalkstack;

#endif /* INC_PSYS_DAT */
