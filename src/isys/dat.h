#ifndef INC_ISYS_DAT
#define INC_ISYS_DAT

/* COPY-PASTE from the initrd dat.h */
struct ent{
	unsigned long magic;
	char name[64];
	unsigned long start;
	unsigned long length;
};

#define MAGIC  0xCAFEBABE
#define NAMESZ 64

#define ENTSZ   sizeof(struct ent)
#define NUMENTS 64
#define SBSZ    NUMENTS *ENTSZ

/* The initramfs */
extern char _binary_initrd_dat_start[];
extern char _binary_initrd_dat_end[];

extern struct ent *superblock;

#endif /* INC_ISYS_DAT */
