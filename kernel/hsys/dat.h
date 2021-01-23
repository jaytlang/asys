#ifndef INC_HSYS_DAT
#define INC_HSYS_DAT

/* Register helpers for traps, interrupts etc. */
#define SSTATUS_SPPMASK 1L << 8
#define SSTATUS_SIEMASK 1L << 1

#define SCAUSE_INTR        1L << 63
#define SCAUSE_EXCODEMASK  0xff
#define EXCODE_EXTERNINTR  9
#define EXCODE_ECALL       8
#define EXCODE_MMODESWINTR 1

/* The timervec machine mode scratch
 * area -- just enough to be able to
 * poke s-mode and reset the timer
 */
struct tinfo{
	unsigned long fakestack[3];
	unsigned long mtimeaddr;
	unsigned long mtimecmpaddr;
	unsigned long interval;
};

extern struct tinfo timerscratch;

/* See hsys/spinlock.c */
extern unsigned long oldintrstate;

#define CLINT         0x2000000L
#define MTIME         CLINT + 0xBFF8
#define MTIMECMP      CLINT + 0x4000
#define TIMERINTERVAL 10000000L

/* Interrupt types */
#define DEVINTR_TIMER 0

#endif /* INC_HSYS_DAT */
