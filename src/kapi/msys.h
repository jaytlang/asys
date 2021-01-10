#ifndef INC_KAPI_MSYS
#define INC_KAPI_MSYS

unsigned long *	setupkvm(void);
void		registerutrap(char *addr);

/* Page allocator */
void		*allocpage(void);
void		freepage(void *page);

/* I'm the map! */
void		map(unsigned long *pgtbl, char *va, char *pa, int perm);

#endif /* INC_KAPI_MSYS */
