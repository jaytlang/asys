/* Process server
 * Programmed in early userland code-style
 * to enable everything to work properly
 * without a dedicated binary
 */
#include "dat.h"

__attribute__((section(".text.ps"))) void
bless(struct psproc *recipient, unsigned long perms)
{
	recipient->permissions |= perms;
}

__attribute__((section(".text.ps"))) unsigned long
checkbless(struct psproc *recipient, unsigned long perm)
{
	return recipient->permissions & perm;
}
__attribute__((section(".text.ps"))) void
psmain(void)
{
	int i;
	char *initialheap;
	struct psproc *me;

	/* hello we exist (: */
	i = pssyscall(SYS_TEST, 0, 0, 0, 0, 0);
	if(i != 0){
		for(;;)
			;
	}

	/* let's make a single psproc for ourselves */
	initialheap =
	    (char *)pssyscall(SYS_GROWBY, sizeof(struct psproc), 0, 0, 0, 0) -
	    sizeof(struct psproc);

	me = (struct psproc *)initialheap;
	me->next = NULL;
	me->pid = 0;

	/* blessings:
	 * -> need to be able to systest
	 * -> need to be able to growby manually
	 *
	 * from now on, check all blessings
	 */
	bless(me, PERM_SYS_TEST);
	bless(me, PERM_SYS_GROWBY);

	/* Manually kick off the initrd process, then wait to receive
	 * messages from any process. TODO
	 */
	for(;;) i++;
}
