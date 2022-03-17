global  _start
extern show_registers
section  .text
_start:
	push 1
	push 2
	pop r14
	pop r12
	sub r12, r14
	push r12
	call show_registers
	mov rax, 60
	mov rdi, 0
	syscall
