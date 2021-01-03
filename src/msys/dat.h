#ifndef INC_MSYS_DAT
#define INC_MSYS_DAT

/* Basic memory layout info */
#define KERNBASE 0x80000000
#define MEMORY_LENGTH 0x10000000
#define MEMORY_TOP 0x90000000

/* Start of free memory, somewhere
 * between KERNBASE and MEMORY_TOP
 */
extern char ekernel[];

/* Physical allocator */
struct freelist{
	struct freelist *next;
};

extern struct freelist *basenode;

/* Page size */
#define PAGESIZE 4096

#endif /* INC_MSYS_DAT */
