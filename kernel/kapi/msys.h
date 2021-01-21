#ifndef INC_KAPI_MSYS
#define INC_KAPI_MSYS

/* Trampoline page. Gets registered at
 * system startup, used in msys/psys.
 */
extern char *utrapaddr;
extern char *kernelstack;
void registerutrap(char *addr);
void registerkstack(char *addr);

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

/* Diet paging */
unsigned long *translateva(unsigned long *pgtbl, char *va);

/* Page size */
#define PAGESIZE 4096

/* Memory mappings - assume a gig */
#define MAXVA    0x3fffffffff
#define UTRAPVEC MAXVA - PAGESIZE + 1
#define UTRAPFRM UTRAPVEC - PAGESIZE

/* User page table utilities */
#define MEMTYPE_GUARD 2
#define MEMTYPE_DATA  1
#define MEMTYPE_CODE  0

#endif /* INC_KAPI_MSYS */
