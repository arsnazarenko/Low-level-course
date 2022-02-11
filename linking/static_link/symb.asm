section .bss    ;   not-initialized data
nx: resq 1024

section .rodata     ; read-only data - constants
const_x: db 1

section .data
x: dq 148842
y: dq x     ; relocation, we use addr of x


extern somewhere     ; relocation, extern function
global _start

section .text

_start:
    mov rax, x
    mov rdx, y
    call somewhere
jmp _start
