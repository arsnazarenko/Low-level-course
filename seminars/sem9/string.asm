section .rodata
message: db ", world!", 10, 0

section .text

extern print_string
extern world

string_length:
  mov rax, 0
    .loop:
      xor rax, rax
    .count:
      cmp byte [rdi+rax], 0
      je .end
      inc rax
      jmp .count
    .end:
      ret

world:
    mov rdi, message

print_string:
    ;   caller-saved, saved before call string_length
    push rax
    ;   callee-saved, saved in print_string
    push rdi
    call string_length
    mov rsi, [rsp]
    mov rdx, rax
    mov rax, 1
    mov rdi, 1
    ;  caller-saved, saved before syscall, because syscall do: rip -> rcx
    push rcx
    syscall
    pop rcx
    pop rdi
    pop rax
    ret

