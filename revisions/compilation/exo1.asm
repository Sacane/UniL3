section .data
    text: db "ouimamacita", 0
    str_fmt: db "%s", 10, 0



section .text

global _start
extern printf



_start:
    push rbp
    mov rbp, rsp

    mov rbx, text
    mov rcx, 0; on met 0 dans rcx
.BOUCLE:
    mov al, byte [rbx]
    cmp al, cl ;ON vérifie que si rax est à 0 (en comparant avec rcx) alors on arrete la boucle
    je .FIN
    sub byte [rbx], 32 ; On soustait à 32 pour obtenir la majuscule
    inc rbx
    jmp .BOUCLE

.FIN:
    mov rsi, text
    mov rdi, str_fmt
    mov al, 0
    call printf
    mov rsp, rbp
    pop rbp
    mov rax, 60
    mov rdi, 0
    syscall
