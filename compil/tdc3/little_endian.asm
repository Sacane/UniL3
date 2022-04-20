section .bss
global_var: resb 8
section .text
global _start
extern show_registers
_start:
	mov 10, [global_var + 4]
	mov 8, [global_var + 0]
	push [global_var + 0]
	push 7
	pop r14
	pop r12
	add r12, r14
	push r12
	push [global_var + 4]
	pop r14
	pop r12
	sub r12, r14
	push r12
    call show_registers
	mov rax, 60
	mov rdi, 0
	syscall
