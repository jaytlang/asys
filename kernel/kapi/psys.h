#ifndef INC_KAPI_PSYS
#define INC_KAPI_PSYS

/* utility to cross module boundary */
void procinitvia(void (*tr)(void));

/* preparation for usermode */
unsigned long *exportupgtbl(void);

/* External scheduler entry */
void suspend(void);

/* Process creation! */
unsigned long srun(unsigned long entrypt, unsigned long start,
                   unsigned long end, char *name);
void scheduler(void);

/* System calls */
void syscall(void);

#endif /* INC_KAPI_PSYS */
