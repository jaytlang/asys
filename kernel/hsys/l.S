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

/* i am the fabric of the universe */
.global llcontextswitch
llcontextswitch:
	sd ra, 0(a0)
	sd s0, 8(a0)
	sd s1, 16(a0)
	sd s2, 24(a0)
	sd s3, 32(a0)
	sd s4, 40(a0)
	sd s5, 48(a0)
	sd s6, 56(a0)
	sd s7, 64(a0)
	sd s8, 72(a0)
	sd s9, 80(a0)
	sd s10, 88(a0)		
	sd s11, 96(a0)

	ld ra, 0(a1)
	ld s0, 8(a1)
	ld s1, 16(a1)
	ld s2, 24(a1)
	ld s3, 32(a1)
	ld s4, 40(a1)
	ld s5, 48(a1)
	ld s6, 56(a1)
	ld s7, 64(a1)
	ld s8, 72(a1)
	ld s9, 80(a1)
	ld s10, 88(a1)		
	ld s11, 96(a1)

	ret

