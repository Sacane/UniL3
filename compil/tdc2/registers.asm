; registers.asm
; registres, chevauchements
section .text
global _start
extern show_registers
extern printf
_start:
	mov rbx, 2
	mov r12, 10
	mov r13, 0
	mov r14, 0
	call show_registers
	; après initialisation
	add rbx, r12
	call show_registers 
	; après addition sur 64 bits
	add bl, 2 ; rbx : 14
	; après addition sur 8 bits
	call show_registers
	mov ebx, 256
	; après copie sur 32 bits
	call show_registers
    mov rax, 0
	mov al,  bh
	mov r13, rax
	; après copie sur 8 bits
	call show_registers
	add bh, 1
	; après addition sur 8 bits
	call show_registers
	mov rax, 60
	mov rdi, 0
	syscall
