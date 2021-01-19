#ifndef INC_KAPI_PSYS
#define INC_KAPI_PSYS

/* utility to cross module boundary */
void procinitvia(void (*tr)(void));

/* preparation for usermode */
void *exporttrapframe(void);
unsigned long *exportupgtbl(void);

/* Internal scheduler entry */
void yield(void);

/* Process creation! */
unsigned long srun(unsigned long entrypt, unsigned long start,
                   unsigned long end, char *name);
void scheduler(void);

#endif /* INC_KAPI_PSYS */
