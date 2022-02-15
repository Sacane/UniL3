section .data
seq_numbers: dq 10, 2, 3, 8, 10, 72, 1, 0
section .text
global _start
extern show_registers

_start:
    
    mov rbx, 0 ;compteur
    mov r12, seq_numbers
    
    push 0 ;Addition
    push 0 ;Maximum
    push 500;Minimum
    push 0;nb No null

    loop:

        mov r14, qword [r12 + rbx]

        
        cmp r14, 0
        jne inc_nonull
        
        cmp r14, qword [rsp + 8]
        jle ifmax
        jge ifmin

        ifmax:
            mov qword [rsp + 8], r14

        ifmin:
            mov qword [rsp + 16], r14

        inc_nonull:
            add qword [rsp + 24], 1

        add rbx, 1 ;Incremente le compteur
        cmp r14, 0
        je endLoop

        jmp loop

    endLoop:

        pop r14
        call show_registers ; expect 7
        pop r14
        call show_registers ; expect 

        pop r14
        call show_registers
        pop r14
        call show_registers


        mov rax, 60
        mov rdi, 0
        syscall

