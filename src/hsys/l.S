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

# Register-granularity operations
.global llwfi
llwfi:
	wfi
	j llwfi

.global llsetsatp
llsetsatp:
	csrw satp, a0
	sfence.vma zero, zero
	ret

.global llsetsepc
llsetsepc:
	csrw sepc, a0
	ret

.global llsetsstatus
llsetsstatus:
	csrw sstatus, a0
	ret

.global llhartid
llhartid:
	mv a0, tp
	ret

.global llsieoff
llsieoff:
	csrr t0, sstatus
	andi t0, t0, ~(1L << 1)
	csrw sstatus, t0
	ret

.global llsieon
llsieon:
	csrr t0, sstatus
	ori t0, t0, (1L << 1)
	csrw sstatus, t0
	ret

.global llgetsie
llgetsie:
	csrr a0, sstatus
	andi a0, a0, (1L << 1)
	srli a0, a0, 1
	ret

.global llclearsip
llclearsip:
	csrr a0, sip
	andi a0, a0, ~(1L << 1)
	csrw sip, a0
	ret
