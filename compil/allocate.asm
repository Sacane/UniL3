section .data
seq_numbers: dw 1, 2, 6, 3, 4, 0
section .text


_start:

    mov rax, 60
    mov rdi, 0
    syscall