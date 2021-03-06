#ifndef INC_MSYS_DAT
#define INC_MSYS_DAT

/* Basic memory layout info */
#define KERNBASE      0x80000000
#define MEMORY_LENGTH 0x10000000
#define MEMORY_TOP    0x90000000

/* Start of free memory, somewhere
 * between KERNBASE and MEMORY_TOP
 */
extern char ekernel[];

/* Start of the data section and the bss */
extern char etext[];

/* Physical allocator */
struct freelist{
	struct freelist *next;
};

extern struct freelist *basenode;
extern unsigned int pglock;

/* Virtual addresses */
#define VAOFFSETBITS 12
#define VALEVELBITS  9

/* PTE flags */
#define PTEV        1 << 0
#define PTER        1 << 1
#define PTEW        1 << 2
#define PTEX        1 << 3
#define PTEU        1 << 4
#define PTEFLAGBITS 10

#endif /* INC_MSYS_DAT */
