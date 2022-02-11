extern _GLOBAL_OFFSET_TABLE

global _start

extern sofun

section .text
_start:
    call sofun wrt ..plt

    mov rdi, 0
    mov rax, 60
    syscall
