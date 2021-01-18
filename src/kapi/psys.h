#ifndef INC_KAPI_PSYS
#define INC_KAPI_PSYS

/* utility to cross module boundary */
void procinitwith(char *kstack);

/* preparation for usermode */
void *exporttrapframe(void);
unsigned long *exportupgtbl(void);

/* Internal scheduler entry */
void yield(void);

#endif /* INC_KAPI_PSYS */
