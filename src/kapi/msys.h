#ifndef INC_KAPI_MSYS
#define INC_KAPI_MSYS

/* Trampoline page. Gets registered at
 * system startup, used in msys/psys.
 */
extern char *utrap;
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

#endif /* INC_KAPI_MSYS */
