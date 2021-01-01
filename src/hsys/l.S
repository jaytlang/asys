# Low level, architecture-specific routines

# Implements CAS
# A0 upon entry: pointer to acquire
# A0 upon return: success (0) or failure (1)
.globl llacquire
llacquire:
	li a1, 1
again:
	amoswap.w.aq a1, a1, (a0)	
	bnez a1, again
	ret

.globl llrelease
llrelease:
	amoswap.w.rl x0, x0, (a0)
	ret
