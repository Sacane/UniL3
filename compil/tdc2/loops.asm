section .text
global _start
extern show_registers
_start:
    mov rbx, 0
    infinite_inc :
        add rbx, 9
        cmp rbx, 100
        jge end
        jmp infinite_inc
    
    end:
        call show_registers
        mov rax, 60
        mov rdi, 0
        syscall