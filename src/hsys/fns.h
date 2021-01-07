#ifndef INC_HSYS_FNS
#define INC_HSYS_FNS

/* Assembly routines in l.S: atomic lock
 * acquisition / swap operations, panic,
 * set some machine regs
 */
extern void llacquire(unsigned int *lock);
extern void llrelease(unsigned int *lock);
extern void llwfi(void);

extern void llsetsatp(unsigned long satp);
extern void llsetsstatus(unsigned long sstatus);
extern void llsetsepc(unsigned long sepc);

extern void llsieoff(void);
extern void llsieon(void);

/* mhartid, aka mv a0, tp because who
 * needs thread local storage? NOT ME
 */
extern unsigned long llhartid(void);

/* Interrupt handling */
int         handledevintr(unsigned long scause);

/* llclearsip: Basically just clear
 * the software interrupt bit in sip
 */
extern void llclearsip(void);


#endif /* INC_HSYS_FNS */
