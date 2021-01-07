/* T r a p p i n g a c t i o n
 * Electric boogaloo
 *
 * mscratch has the tinfo structure
 * MACHINE MODE
 */
.global llmtraptimer
llmtraptimer:
	csrrw a0, mscratch, a0
	sd a1, 0(a0)
	sd a2, 8(a0)
	sd a3, 16(a0)

	/* a1 contains location of mtimecmp
	 * a2 contains current mtimecmp
	 * a3 contains the interval, hard-coded
	 */
	ld a1, 32(a0)
	ld a2, 0(a1)
	ld a3, 40(a0)

	add a2, a2, a3
	sd a2, 0(a1)

	/* Supervisor interrupt */
	li a1, (1L << 1)
	csrw sip, a1

	ld a3, 16(a0)
	ld a2, 8(a0)
	ld a1, 0(a0)
	csrrw a0, mscratch, a0
	mret
