/* User mode syscall shim */
.section .text.ps
.global pssyscall
pssyscall:
	ecall
	ret

