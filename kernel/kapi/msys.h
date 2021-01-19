#ifndef INC_KAPI_MSYS
#define INC_KAPI_MSYS

/* Trampoline page. Gets registered at
 * system startup, used in msys/psys.
 */
extern char *utrapaddr;
void registerutrap(char *addr);

/* Kernel page table.
 * Unsigned long because it's
 * an array of PPN + flags values, which
 * are each 64-bit aligned (zero extend)
 */
extern unsigned long *kpgtbl;

void setupkvm(void);

/* Page allocator */
void *allocpage(void);
void freepage(void *page);

/* User page table */
unsigned long *mkupgtbl(char *trapframe);
void mkuserpages(unsigned long *pgtbl, unsigned long oldsz, unsigned long newsz,
                 int mtype);

#define MEMTYPE_DATA 1
#define MEMTYPE_CODE 0

#endif /* INC_KAPI_MSYS */
