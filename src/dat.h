/* jsyskrn.exe: Data structures and definitions.
 * Copyright Jay Lang, 2020
 */
#ifndef INC_JSYSKRN_DAT
#define INC_JSYSKRN_DAT

/* Kernel stack */
__attribute__((aligned(16))) extern char kstack[4096];

/* The trampoline, passed to psys at startup */
extern char llutrap[], lluret[];

/* The system trap vector, handled in m-mode */
extern char llstrap[];

/* The initramfs */
extern char _binary_initrd_dat_start[];
extern char _binary_initrd_dat_end[];
extern char startps[], endps[];

#endif /* INC_JSYSKRN_DAT */
