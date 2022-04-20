section .bss
global_var: resq 2
main: resq 1
section  .text
global  _start
extern my_putchar
extern my_getint
_start:
	mov rdi, 'W'
	call my_putchar
	mov rdi, 'e'
	call my_putchar
	mov rdi, ' '
	call my_putchar
	mov rdi, 'g'
	call my_putchar
	mov rdi, 'o'
	call my_putchar
	mov rdi, 't'
	call my_putchar
	mov rdi, ' '
	call my_putchar
	mov rdi, 'p'
	call my_putchar
	mov rdi, 'u'
	call my_putchar
	mov rdi, 't'
	call my_putchar
	mov rdi, 'c'
	call my_putchar
	mov rdi, 'h'
	call my_putchar
	mov rdi, 'a'
	call my_putchar
	mov rdi, 'r'
	call my_putchar
	mov rdi, 13
	call my_putchar
	mov rdi, 10
	call my_putchar
	mov rax, 60
	mov rdi, 0
	syscall

