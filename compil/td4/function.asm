section .text
extern show_registers
global pow2

pow2:

    mov rax, rdi
    imul rax, rdi
    ret







