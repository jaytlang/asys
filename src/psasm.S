.section .text.ps
.global dosyscall
dosyscall:
	ecall
	ret

