section .bss
global_vars: resq 1
main: resq 2
section .data
	msg1: db "%d", 10, 0
section  .text
     global  _start
     extern my_putchar
     extern show_registers
     extern my_getint
     extern printf
     _start:
	mov qword [main + 8], 'M'
	push 19
	push 19
	pop rcx
	pop rax
	sub rax, rcx
	push rax
	mov r12, rax
	mov qword [main + 0], rax
	mov rax, 0
	mov rbx, 0
	mov qword [global_vars + 0], 0
	mov rdi, 'p'
	call my_putchar
	add rbx, qword [main + 8]
	jg labelId_1
	jmp labelElse_1
labelId_1:
	mov rdi, 'I'
	call my_putchar
	mov rdi, 'F'
	call my_putchar
	mov rdi, `\n`
	call my_putchar
	jmp labelCode_1
labelElse_1:
	mov rdi, 'E'
	call my_putchar
	mov rdi, 'L'
	call my_putchar
	mov rdi, 'S'
	call my_putchar
	mov rdi, 'E'
	call my_putchar
	mov rdi, `\n`
	call my_putchar
labelCode_1:
	mov rdi, 'E'
	call my_putchar
	mov rdi, 'N'
	call my_putchar
	mov rdi, 'D'
	call my_putchar
	mov rdi, `\n`
	call my_putchar


	;Trying to use printf
	push 10
	pop rsi
	mov rax, 0
	mov rdi, msg1
	call printf
	mov rsi, 20
	mov rax, 0
	mov rdi, msg1
	call printf
	mov rsi, 1029
	mov rax, 0
	mov rdi, msg
	call printf
	mov rax, 60
	mov rdi, 0
	syscall

