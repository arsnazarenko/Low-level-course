%define buff_size 255
%define key_offset 8
section .rodata

%include "err_msg.inc"
%include "words.inc"


section .bss
buffer: resb buff_size


section .text

%include "lib.inc"
%include "dict.inc"

global _start

_start:
    mov rdi, buffer
    mov rsi, buff_size
    call read_line
    push rax
    call print_newline
    pop rax
    cmp rax, 0
    je .buff_overflow
    mov rdi, buffer
    mov rsi, last_node
    call find_word
    push rax
    pop rax
    cmp rax, 0
    je .not_found
    lea rdi, [rax + key_offset]    		; key addr
    push rax
    call string_length
    mov rdx, rax            			; rdx - len of key
    inc rdx                             ; add '\0' to length
    pop rax                 			; rax - addr of node in dict
    lea rdi, [rax + rdx + key_offset]   ; rdi - addr of value str
    mov rsi, STDOUT
    call print_string
    call print_newline
    mov rdi, EXIT_SUCCESS
    jmp exit
.not_found:
    mov rdi, not_found_msg
    jmp .err
.buff_overflow:
    mov rdi, buff_overflow_msg
.err:
    mov rsi, STDERR
    call print_string
    mov rdi, EXIT_FAILURE
    jmp exit
