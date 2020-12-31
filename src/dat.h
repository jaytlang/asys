/* jsyskrn.exe: Data structures and definitions.
 * Copyright Jay Lang, 2020
 */

#ifndef INC_JSYSKRN_DAT
#define INC_JSYSKRN_DAT

/* Kernel stack */
__attribute__((aligned(16))) extern char kstack[4096];

#endif /* INC_JSYSKRN_DAT */
