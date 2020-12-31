/* jsyskrn.exe initialization code
 * Copyright Jay Lang, 2020
 */

.section .text.init
.global _start
_start:
	csrr a0, mhartid
	bnez a0, spin

	la sp, kstack
	li t0, 4096
	add sp, sp, t0
	call main
spin:
	j spin
