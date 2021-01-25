#include "dat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The database people are going to
 * hate my guts for this...
 */

int
main(int argc, char *argv[])
{
	struct ent superblock[NUMENTS];
	unsigned char *entrybuf;
	int i, lenctr;
	FILE *fd, *sfd;

	if(argc < 2){
		printf("error: no files provided\n");
		printf("usage: ./generate [FILES]\n");
		return 1;

	}else if(argc > NUMENTS + 1){
		printf("error: too many files provided\n");
		printf("the initrd supports up to %d files\n", NUMENTS);
		return 1;
	}

	printf("asys initrd generator\n\n");

	fd = fopen(INITRD, "w+");
	lenctr = SBSZ;

	/* Dry run: determine all the right values */
	printf("superblock size is %x bytes\n", SBSZ);
	printf("populating superblock");
	for(i = 0; i < (argc - 1); i++){
		superblock[i].magic = MAGIC;
		strncpy(superblock[i].name, argv[i + 1], NAMESZ);

		superblock[i].start = lenctr;
		superblock[i].length = flength(argv[i + 1]);
		lenctr += flength(argv[i + 1]);
		printf(".");
	}

	printf("done\n");
	printf("total initrd length will be %x bytes\n", lenctr);

	/* Populate the initrd */
	fwrite(superblock, ENTSZ, NUMENTS, fd);

	printf("writing initramfs contents...\n");
	for(i = 0; i < (argc - 1); i++){
		entrybuf = (unsigned char *)malloc(superblock[i].length);
		sfd = fopen(superblock[i].name, "r");
		fread(entrybuf, superblock[i].length, 1, sfd);
		fwrite(entrybuf, superblock[i].length, 1, fd);

		printf("\t%s (%x bytes) -> 0x%x\n", superblock[i].name,
		       superblock[i].length, superblock[i].start);

		fclose(sfd);
		free(entrybuf);
	}

	printf("initrd is ready\n");
	fclose(fd);
	return 0;
}

long
flength(char *path)
{
	FILE *stream;
	long result;

	/* a nice plan 9 seek call would fit here... */
	stream = fopen(path, "r");
	fseek(stream, 0, SEEK_END);
	result = ftell(stream);

	fclose(stream);
	return result;
}
