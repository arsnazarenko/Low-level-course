section .data
message: db "hello, world!", 10

section .text
global _start

exit:
    mov rax, 60
    syscall

; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
    xor rax, rax
.loop: 
    cmp byte [rdi + rax], 0
    je .end
	inc rax
    jmp .loop
.end: 
    ret

; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
    push rdi
    call string_length      ; string length in rax
    pop rdi
    mov rdx, rax            ; rdx - length in bytes
    mov rax, 1              ; 'write' syscall number
    mov rsi, rdi            ; address
    mov rdi, 1              ; stdout
    syscall
    ret

func:
    push rbp
    mov rbp, rsp

    mov rbp, rsp
    xor rax, rax
    add rax, rdi
    add rax, rsi
    add rax, rdx
    add rax, rcx
    add rax, r8
    add rax, r9
    add rax, [rbp - 8]
    add rax, [rbp - 16]
    pop rbp
    mov rsp, rbp
    ret


_start:
    mov rdi, message
    push rdi
    call print_string
    pop rdi
    call print_string
    mov rdi, 1
    mov rsi, 2
    mov rdx, 3
    mov rcx, 4
    mov r8, 5
    mov r9, 6
    sub rsp, 16
    mov rax, 7
    mov qword [rsp - 8], rax
    mov rax, 8
    mov qword [rsp - 16], rax
    call func
    call exit

