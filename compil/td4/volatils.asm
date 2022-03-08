section .data 
number1 dd 1 
number2 dd 10


section .text
extern show_registers
global _start
extern show_stack

swap:
    mov rax, number1
    mov rdx, number2
    ;rax -> 1
    ;rdx -> 10
    mov rcx, rax
    ;rcx -> 1
    call show_stack
    mov [number2], rax
    ;rax -> 10
    mov [number1], rcx
    ;rdx -> 1

    ret


_start:
    mov rdi, number1
    mov rsi, number2

    call show_stack
    

    mov rbx, number1
    mov r12, number2
    call show_registers

    call swap

    call show_registers

    mov rax, 60
    mov rdi, 0
    syscall