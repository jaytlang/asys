/* From userland, switch into the kernel
 * and back to userland. Mapped to the highest
 * page of memory. sscratch contains a pointer
 * to the process's trap frame.
 */

.section .text.utrap
.global llutrap
llutrap:
	/* sscratch has the p->trapframe page
	 * we will skip epc for now, but save
	 * everything else before jumping into
	 * psys. no arguments (obviously).
	 */
	csrrw a0, sscratch, a0
	sd ra, 32(a0)
	sd sp, 40(a0)
	sd gp, 48(a0)
#	sd a0, 56(a0)
	sd a1, 64(a0)
	sd a2, 72(a0)
	sd a3, 80(a0)
	sd a4, 88(a0)
	sd a5, 96(a0)
	sd a6, 104(a0)
	sd a7, 112(a0)
	sd s0, 120(a0)
	sd s1, 128(a0)
	sd s2, 136(a0)
	sd s3, 144(a0)
	sd s4, 152(a0)
	sd s5, 160(a0)
	sd s6, 168(a0)
	sd s7, 176(a0)
	sd s8, 184(a0)
	sd s9, 192(a0)
	sd s10, 200(a0)
	sd s11, 208(a0)
	sd t0, 216(a0)
	sd t1, 224(a0)
	sd t2, 232(a0)
	sd t3, 240(a0)
	sd t4, 248(a0)
	sd t5, 256(a0)
	sd t6, 264(a0)

	csrr t0, sscratch
	sd t0, 56(a0)

	/* first, sepc */
	csrr t0, sepc
	sd t0, 24(a0)

	/* next, the stack */
	ld sp, 16(a0)
	
	/* ready to make the jump. load stage two. */
	ld t5, 0(a0)

	/* load in kpgtbl. a0 is bad after csrw. */
	ld t0, 8(a0)
	srli t0, t0, 12
	li t1, 8L
	slli t1, t1, 60

	or t0, t0, t1
	csrw satp, t0
	sfence.vma zero, zero

	/* we have entered kernel mode formally.
	 * set the interrupt vector LATER.
	 * go to C using t5, or stg2.
	 */
	csrr a0, sstatus
	csrr a1, scause
	la a2, lluret
	jr t5

.global lluret
lluret:

	/* restore sstatus to usermode w/ interrupts */
	csrr t0, sstatus
	andi t0, t0, ~(1L << 8)
	ori t0, t0, (1L << 5)
	csrw sstatus, t0

	/* write stvec to utrap */
	la t0, llutrap
	csrw stvec, t0

	/* lluret(upgtbl, tf)
	 * first restore upgtbl.
	 * we can't do this inside the
	 * kernel, else any code we try
	 * to execute (e.g. this call)
	 * will page fault instantly
	 */
	srli t0, a0, 12
	li t1, 8L
	slli t1, t1, 60
	or t0, t0, t1
	csrw satp, t0
	sfence.vma zero, zero

	/* trash a0 now that we're done
	 * and continue restoration
	 */
	mv a0, a1

	/* a0 has tf. restore sepc */
	ld t0, 24(a0)
	csrw sepc, t0

	/* register time */
	ld t0, 56(a0)
	csrw sscratch, t0

	ld ra, 32(a0)
	ld sp, 40(a0)
	ld gp, 48(a0)
#	ld a0, 56(a0)
	ld a1, 64(a0)
	ld a2, 72(a0)
	ld a3, 80(a0)
	ld a4, 88(a0)
	ld a5, 96(a0)
	ld a6, 104(a0)
	ld a7, 112(a0)
	ld s0, 120(a0)
	ld s1, 128(a0)
	ld s2, 136(a0)
	ld s3, 144(a0)
	ld s4, 152(a0)
	ld s5, 160(a0)
	ld s6, 168(a0)
	ld s7, 176(a0)
	ld s8, 184(a0)
	ld s9, 192(a0)
	ld s10, 200(a0)
	ld s11, 208(a0)
	ld t0, 216(a0)
	ld t1, 224(a0)
	ld t2, 232(a0)
	ld t3, 240(a0)
	ld t4, 248(a0)
	ld t5, 256(a0)
	ld t6, 264(a0)

	csrrw a0, sscratch, a0
	sret

