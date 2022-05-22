section .text

global _start
extern printf

_start:
    push rbp
    mov rbp, rsp
    push 0
    mov qword [rsp], 10
    mov qword [rsp+8], 4

    mov rsi, rsp
    mov rdi, rsp
    add rdi, 8

    mov rbx, qword [rsi]
    mov qword [rdi], rbx
    mov rsp, rbp

    pop rbp
    mov rax, 60
    mov rdi, qword [rdi]
    syscall