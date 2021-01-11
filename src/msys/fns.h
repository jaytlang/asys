#ifndef INC_MSYS_FNS
#define INC_MSYS_FNS

/* Helper function definitions private
 * to msys. These don't have checked params.
 */
unsigned long 	indexfromva(char *va, unsigned int level);
char *		physviapte(unsigned long pte);
unsigned long	pteviaphys(char *phys);

/* Page-table-level operations - i.e., walk-y things
 * Both of these return PTEs
 */
unsigned long * descendonce(unsigned long *pgtbl, char *va, unsigned int level);
unsigned long *	pteforva(unsigned long *pgtbl, char *va);

/* Page allocator private methods */
void		initpagealloc(void);

/* I'm the map! */
void		map(unsigned long *pgtbl, char *va, char *pa, int perm);


#endif /* INC_MSYS_FNS */
