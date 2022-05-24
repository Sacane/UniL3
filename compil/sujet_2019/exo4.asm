; expand32.asm
section .data
    source: dd 345, 3, 12, 728, 728, 730
section .bss
    destination: resq 6
section .text
global _start
extern show_registers
_start:
    ; `a compl´eter

    mov rbx, 0
    mov r13d, 0
    mov r14, 0

    boucle:
        
        mov r12d, dword [source + r14]
        mov qword [destination + rbx], r12
        
        call show_registers
        
        add r14, 4
        add rbx, 1
        cmp rbx, 6
        jne boucle

    mov rax,60
    mov rdi, 0

    syscall