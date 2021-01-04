# Low level, architecture-specific routines
# Yeah, most of this is architecture specific,
# but if you need something in assembly or with
# thin C wrappers this is the subsystem for you

# Implements CAS
# A0 upon entry: pointer to acquire
# A0 upon return: success (0) or failure (1)
.global llacquire
llacquire:
	li a1, 1
again:
	amoswap.w.aq a1, a1, (a0)	
	bnez a1, again
	ret

.global llrelease
llrelease:
	amoswap.w.rl x0, x0, (a0)
	ret

# WFI loop -- low power state
.global llwfi
llwfi:
	wfi
	j llwfi

.global llsetsatp
llsetsatp:
	csrw satp, a0
	sfence.vma zero, zero
	ret

