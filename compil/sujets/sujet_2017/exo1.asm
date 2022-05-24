
section .text
global _start
extern show_registers

;On met 
int_cmp:
    ; à compléter

    cmp rdi, rsi
    jg greater
    je equal
    jl lower
    greater:
        mov rax, 1
        jmp end
    equal:
        mov rax, 0
        jmp end
    lower:
        mov rax, -1
        jmp end

    end:
        ret


swap:

    mov eax, dword [rdi]
    mov ecx, dword [rsi]
    mov dword [rdi], ecx
    mov dword [rsi], eax
    ret

_start:

    mov rdi, 60
    mov rsi, 20

    call int_cmp
    mov rbx, rax
    call show_registers; rax should be 1

    ;start swap

    

    mov rax, 60
    mov rdi, 0
    syscall 