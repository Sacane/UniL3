section .data
my_bytes: db 1, 2, 3, 4
my_words: dd 4, 3, 2, 1
section .text

global _start
extern printf

_start:
    push 2
    push 3 
    push 3
    pop rbx
    pop rax 
    imul rax, rbx
    push rax
    push 2 
    push 3
    pop rbx
    pop rax
    imul rax, rbx
    push rax
    pop rbx
    pop rax
    sub rax, rbx
    push rax
    push 1
    pop rbx
    pop rax
    add rax, rbx
    push rax
    pop rbx
    pop rax 
    imul rax, rbx
    push rax
    mov rdx, rbx
    mov rax, 60
    mov rdi, rdx
    syscall