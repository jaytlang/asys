/* jsyskrn.exe initialization code
 * Copyright Jay Lang, 2020
 */

.section .text.init
.global _start
_start:
	csrr a0, mhartid
	bnez a0, spin
	mv tp, a0

	la sp, kstack
	li t0, 4096
	add sp, sp, t0

	/* Get the address of the timer scratch
	 * area into a0, now that we've a stack
	 * for C to get going. Then store it into
	 * mscratch
	 */
	call mktimerscratch
	csrw mscratch, a0

	/* Configure machine mode timer interrupts */
	la t0, llmtraptimer
	csrw mtvec, t0

	csrr t0, mie
	ori t0, t0, (1L << 7)
	csrw mie, t0

	/* Enable machine mode interrupts per mstatus, while
	 * preparing for supervisor mode (previous mode) */
	li t0, (1L << 11)
	csrw mstatus, t0

	/* Start the timer ticking now that we're good to go...
	 * a0 at offset 24 has the address, 32 the interval.
	 * t1 is the current mtimecmp address
	 * t2 is the current mtime address
	 * t3 is the current mtime value
	 * t4 is interval
	 */
	ld t1, 32(a0)
	ld t2, 24(a0)
	ld t3, 0(t2)
	ld t4, 40(a0)

	add t4, t3, t4
	sd t4, 0(t1)

	/* Explicitly delegate interrupts and excepts to s mode.
	 * Enable all s-mode interrupts. 16 plus are reserved per
	 * the risc-v spec, so just cover these for now
	 */
	li t0, 0xffff
	csrw medeleg, t0
	li t0, 0xffff
	csrw mideleg, t0 

	csrr t0, sie
	ori t0, t0, (1L << 1) | (1L << 5) | (1L << 9)
	csrw sie, t0

	/* Set the s-mode trap handler */
	la t0, llstrap
	csrw stvec, t0

	/* Set program counter to main and go */
	la t0, main
	csrw mepc, t0
	mret

spin:
	wfi
	j spin

/* T r a p p i n g a c t i o n
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

/* Supervisor trap vector
 * Gang gang
 */

 .global llstrap
 llstrap:
    addi sp, sp, -256

    sd ra, 0(sp)
    sd sp, 8(sp)
    sd gp, 16(sp)
#   sd tp, 24(sp)
    sd a0, 32(sp)
    sd a1, 40(sp)
    sd a2, 48(sp)
    sd a3, 56(sp)
    sd a4, 64(sp)
    sd a5, 72(sp)
    sd a6, 80(sp)
    sd a7, 88(sp)
    sd s0, 96(sp)
    sd s1, 104(sp)
    sd s2, 112(sp)
    sd s3, 120(sp)
    sd s4, 128(sp)
    sd s5, 136(sp)
    sd s6, 144(sp)
    sd s7, 152(sp)
    sd s8, 160(sp)
    sd s9, 168(sp)
    sd s10, 176(sp)
    sd s11, 184(sp)
    sd t0, 192(sp)
    sd t1, 200(sp)
    sd t2, 208(sp)
    sd t3, 216(sp)
    sd t4, 224(sp)
    sd t5, 232(sp)
    sd t6, 240(sp)

    csrr a0, sepc
    csrr a1, sstatus
    csrr a2, scause
    call ktrap

    ld ra, 0(sp)
    ld sp, 8(sp)
    ld gp, 16(sp)
#   ld tp, 24(sp)
    ld a0, 32(sp)
    ld a1, 40(sp)
    ld a2, 48(sp)
    ld a3, 56(sp)
    ld a4, 64(sp)
    ld a5, 72(sp)
    ld a6, 80(sp)
    ld a7, 88(sp)
    ld s0, 96(sp)
    ld s1, 104(sp)
    ld s2, 112(sp)
    ld s3, 120(sp)
    ld s4, 128(sp)
    ld s5, 136(sp)
    ld s6, 144(sp)
    ld s7, 152(sp)
    ld s8, 160(sp)
    ld s9, 168(sp)
    ld s10, 176(sp)
    ld s11, 184(sp)
    ld t0, 192(sp)
    ld t1, 200(sp)
    ld t2, 208(sp)
    ld t3, 216(sp)
    ld t4, 224(sp)
    ld t5, 232(sp)
    ld t6, 240(sp)

    addi sp, sp, 256
    sret
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

