/* Basic userland to start */
.section .text.one
.global one
one:
	addi a0, a0, 1
	j one

