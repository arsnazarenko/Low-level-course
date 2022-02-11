section .data
s1: db "mashamasha", 0

section .text

global _start

%define EXIT_OK 0
%include "lib.inc"
		
_start:
    mov rdi, -1
    call print_int
    call print_newline
    mov rdi, s1
    call print_string
    call print_newline
    mov rdi, s1
    mov rsi, 6
    call read_word
    cmp rax, 0
    je .ex
    push rax
    mov rdi, rax
    call print_string
    call print_newline
    pop rax
    sub rsp, 6
    mov rdi, rax
    mov rsi, rsp
    mov rdx, 6
    call string_copy
    mov rdi, rsp
    call print_string
    call print_newline
    mov rdi, rsp
    call parse_int
    test rdx, rdx
    jz .ex
    mov rdi, rax
    call print_int
    call print_newline
    add rsp, 6
.ex:
    mov rdi, EXIT_OK
    call exit
