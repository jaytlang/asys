/* Basic userland to start */
.section .text.one
.global one
one:
	li a7, 1
	ecall
hangout:
	addi a0, a0, 1
	j hangout

