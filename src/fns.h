/* jsyskrn.exe: Function definitions.
 * Copyright Jay Lang, 2020
 */

#ifndef INC_JSYSKRN_FNS
#define INC_JSYSKRN_FNS

int main();

/* usermode bootstrap */
void rsmain(void);

/* cross module functionality to
 * avoid troubles with circular dependencies
 */
void newproctotrapret(void);

#endif /* INC_JSYSKRN_FNS */
