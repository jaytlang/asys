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
