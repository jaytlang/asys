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
	sd ra, 24(a0)
	sd sp, 32(a0)
	sd gp, 40(a0)
#	sd a0, 48(a0)
	sd a1, 56(a0)
	sd a2, 64(a0)
	sd a3, 72(a0)
	sd a4, 80(a0)
	sd a5, 88(a0)
	sd a6, 96(a0)
	sd a7, 104(a0)
	sd s0, 112(a0)
	sd s1, 120(a0)
	sd s2, 128(a0)
	sd s3, 136(a0)
	sd s4, 144(a0)
	sd s5, 152(a0)
	sd s6, 160(a0)
	sd s7, 168(a0)
	sd s8, 176(a0)
	sd s9, 184(a0)
	sd s10, 192(a0)
	sd s11, 200(a0)
	sd t0, 208(a0)
	sd t1, 216(a0)
	sd t2, 224(a0)
	sd t3, 232(a0)
	sd t4, 240(a0)
	sd t5, 248(a0)
	sd t6, 256(a0)

	/* context saved. les go!
	 * fresh entry into the kernel
	 * -> start at the top of the stack
	 */
	csrr t0, sscratch
	sd t0, 48(a0)
	
	la sp, kstack
	li t0, 4096
	add sp, sp, t0
	
	/* load in stage 2 and kpgtbl */
	ld t0, 8(a0)
	ld t1, 0(a0)
	csrw satp, t1
	sfence.vma zero, zero

	jr t0

.global lluret
lluret:
	/* lluret(trapframe, upgtbl)
	 * first restore upgtbl.
	 * we can't do this inside the
	 * kernel, else any code we try
	 * to execute (e.g. this call)
	 * will page fault instantly
	 */
	csrw satp, a1
	sfence.vma zero, zero

	ld t0, 48(a0)
	csrw sscratch, t0

	ld ra, 24(a0)
	ld sp, 32(a0)
	ld gp, 40(a0)
#	ld a0, 48(a0)
	ld a1, 56(a0)
	ld a2, 64(a0)
	ld a3, 72(a0)
	ld a4, 80(a0)
	ld a5, 88(a0)
	ld a6, 96(a0)
	ld a7, 104(a0)
	ld s0, 112(a0)
	ld s1, 120(a0)
	ld s2, 128(a0)
	ld s3, 136(a0)
	ld s4, 144(a0)
	ld s5, 152(a0)
	ld s6, 160(a0)
	ld s7, 168(a0)
	ld s8, 176(a0)
	ld s9, 184(a0)
	ld s10, 192(a0)
	ld s11, 200(a0)
	ld t0, 208(a0)
	ld t1, 216(a0)
	ld t2, 224(a0)
	ld t3, 232(a0)
	ld t4, 240(a0)
	ld t5, 248(a0)
	ld t6, 256(a0)

	csrrw a0, sscratch, a0
	sret

