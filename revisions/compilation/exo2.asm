section .data
my_bytes: db 1, 2, 3, 4
my_words: dd 4, 3, 2, 1
section .text

global _start
extern printf

_start:
    mov rax, 0
    mov al, byte[my_bytes]
    mov rbx, 0
    mov bl, byte[my_bytes+3]
    mov rcx, 0
    mov cx, word [my_words+2]
    mov rdx, 0
    mov dl, byte [my_words+3]
    mov rax, 60
    mov rdi, rcx
    syscall