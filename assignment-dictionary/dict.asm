%define key_offset 8


section .text

extern string_equals

global find_word


; rdi - key, rsi - addr of node
find_word:
    ;mov r8, rdi
    ;mov r9, rsi
.loop:
    cmp rsi, 0
    je .not_found
    push rdi
    push rsi
    lea rsi, [rsi + key_offset]
    call string_equals
    pop rsi
    pop rdi
    cmp rax, 1
    je .found
    mov rsi, qword[rsi]
    jmp .loop
.found:
    mov rax, rsi
    ret
.not_found:
    xor rax, rax
    ret


    
