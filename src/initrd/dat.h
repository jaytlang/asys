#ifndef INC_INITRDGEN_DAT
#define INC_INITRDGEN_DAT

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

#define INITRD "initrd.dat"

long flength(char *path);

#endif /* INC_INITRDGEN_DAT */
