BITS 64

.rodata:
    text: db "Hello, World!", 0  ; 13 characters

.text:
    global _start

_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, text
    mov rdx, 13
    syscall
    mov rax, 60
    mov rdi, 0
    syscall
