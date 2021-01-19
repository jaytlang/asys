/* jsyskrn.exe: Function definitions.
 * Copyright Jay Lang, 2020
 */

#ifndef INC_JSYSKRN_FNS
#define INC_JSYSKRN_FNS

int main();

/* Cross module stuff */
void newproctotrapret(void);

/* Return to userspace */
extern void lluret(unsigned long *upgtbl, void *tf);

/* usermode tests */
void testprocone(void);
void testproctwo(void);

#endif /* INC_JSYSKRN_FNS */
