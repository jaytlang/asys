/* jsyskrn.exe initialization code
 * Copyright Jay Lang, 2020
 */

.section .text.init
.global _start
_start:
	csrr a0, mhartid
	bnez a0, spin

	/* Get ready for supervisor
	 * mode, so we don't needa jump
	 * that gap later on. Interrupts
	 * get enabled here eventually,
	 * disable them for now.
	 */
	li t0, (1 << 11)	/* supervisor mode */
	csrw mstatus, t0
	csrw mie, x0

	la sp, kstack
	li t0, 4096
	add sp, sp, t0

	la t0, main
	csrw mepc, t0
	mret
spin:
	j spin
