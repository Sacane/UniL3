

section .text
global _start
extern show_registers
_start:
    mov rbx, 10
    mov r12, 10
    mov r13, 1
    call show_registers
    
    cmp rbx, r12
    jg is_more
    jl is_less
    je is_equal

    
    is_more:
        mov rax, 60
        mov rdi, 1
        jmp end
    is_less:
        mov rax, 60
        mov rdi, -1
        jmp end
    is_equal:
        mov rax, 60
        mov rdi, 0
        jmp end
    end:
        syscall