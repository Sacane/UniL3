section .text
global _start
extern show_registers
extern pow2

_start:
    mov rdi, 8 ;On veut connaitre le carré de 8
    call pow2
    mov r12, rax 
    call show_registers 
    mov rax, 60
    mov rdi, 0
    syscall

