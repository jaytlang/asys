#ifndef INC_KAPI_LSYS
#define INC_KAPI_LSYS

/* The in-kernel libc. Really simple stuff,
 * just useful for strcpy, memset, etc.
 */
void *memset(void *region, char byte, unsigned int count);
void *memcpy(void *dest, void *src, unsigned int count);

unsigned long roundup(unsigned long input, unsigned long roundto);
unsigned long rounddown(unsigned long input, unsigned long roundto);

unsigned long strlen(char *c);

#define NULL ((void *)0)

/* Errno */
#define ENOMEM -1

#endif /* INC_KAPI_LSYS */
