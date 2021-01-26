.section .text.ps
.global testsyscall
testsyscall:
	li a0, 0
	ecall
	li a0, 5
	ecall
	ret

