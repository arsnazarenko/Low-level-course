%define SYS_READ 0
%define SYS_WRITE 1
%define SYS_EXIT 60
%define STDOUT 1
%define STDIN 0
%define NULL_TERMINATOR 0
%define LINE_FEED 0xA
%define SPACE 0x20
%define TAB 0x9

section .text

global exit
global string_length
global print_string
global print_newline
global print_char
global print_uint
global print_int
global string_equals
global read_char
global read_word
global parse_uint
global parse_int
global string_copy
global read_line


 
 
; Принимает код возврата и завершает текущий процесс
exit:
    mov rax, SYS_EXIT
    syscall 

; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
    xor rax, rax
.loop: 
    cmp byte [rdi + rax], NULL_TERMINATOR
    je .end
	inc rax
    jmp .loop
.end: 
    ret

; Принимает указатель на нуль-терминированную строку в rdi, поток вывода в rsi
; выводит её в указанный поток
print_string:
    push rdi
    push rsi
    call string_length      ; string length in rax
    pop rsi
    pop rdi
    mov r8, rsi             ; save rsi
    mov rsi, rdi            ; address
    mov rdx, rax            ; rdx - length in bytes
    mov rax, SYS_WRITE      ; 'write' syscall number
    mov rdi, r8             ; output stream
    syscall
    ret


; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    mov rdi, LINE_FEED
print_char:
    push rdi                ; push symbol ascii code on the stack
    mov rdx, 1              ; rdx - length in bytes
    mov rax, SYS_WRITE      ; 'write' syscall number
    mov rsi, rsp            ; address
    mov rdi, STDOUT         ; stdout
    syscall
    pop rdi						
    ret


; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
	push rbp    			; save calee-saved registers
	push r12
    mov rbp, rsp	
	mov rax, rdi			; rax - dividend
	mov r12, 10				; r12 - divider
	sub rsp, 1				; reserve 1 byte on the stack
	mov byte[rsp], NULL_TERMINATOR		; push null terminator
.loop:
    xor rdx, rdx			; clear prev. remainder
    div r12
    add rdx, '0'			; get ascii code from remainder
    sub rsp, 1				; push code value on stack
    mov byte [rsp], dl		; dl - low 8-bits of rdx
    test rax, rax
    jz .print				; if rax = 0 -> print_string
    jmp .loop
.print:
    mov rdi, rsp
    mov rsi, STDOUT
    call print_string
    mov rsp, rbp			;restore callee-saved registers 
    pop r12
    pop rbp
    ret

; Выводит знаковое 8-байтовое число в десятичном формате 
print_int:
    test rdi, rdi			; check signed or unsigned
    jns print_uint			; if positive -> print_uint
    push rdi				; caller-saved, save before call print_char
    mov rdi, '-'			; print "-"
    call print_char
    pop rdi
    neg rdi					; create positive from negative
    jmp print_uint

; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
	mov rax, 0
	xor rdx, rdx
	xor rcx, rcx
.loop:
    mov cl, byte[rsi + rdx]
    cmp byte[rdi + rdx], cl
    jne .not_equals			                ; if a[i] != b[i] -> not equals	
    cmp byte[rdi + rdx], NULL_TERMINATOR	; if a[i] != b[i] && a[i] == '0' -> equals
    je .equals
    inc rdx  					
    jmp .loop 				
.equals:
    mov rax, 1 
.not_equals:
    ret

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    mov rdi, STDIN          ; stdin
    mov rax, SYS_READ       ; read - 0 
    sub rsp, 1              ; create buffer
    mov byte[rsp], 0        
    mov rsi, rsp            ; buffer addr
    mov rdx, 1              ; size in bytes
    syscall
    mov al, byte[rsp]       ; if syscall read ret eof -> al = 0
    add rsp, 1
    ret

; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор


; rdi - buff addr, rsi - buff size
read_word:
    xor r8, r8              ; size of word
.start:
    push r8
    push rdi
    push rsi
    call read_char          ; read new char
    pop rsi
    pop rdi
    pop r8
    cmp al, SPACE            ; if char == \s -> .start
    je .start
    cmp al, TAB             ; if char == \s -> .start
    je .start
    cmp al, LINE_FEED
    je .start               ; if char == \s -> .start
    test al, al             ; if read_char ret eof (string = \0) -> .ok
    jz .ok
.char:
    mov byte[rdi + r8], al  ; move char to buffer
    inc r8                  ; len++
    push r8
    push rdi
    push rsi
    call read_char
    pop rsi
    pop rdi
    pop r8
    cmp al, SPACE           ; if char == \s = .eof (end of this string)
    je .eof
    cmp al, TAB             ; if char == \s = .eof (end of this string)
    je .eof                 
    cmp al, LINE_FEED       ; if char == \s = .eof (end of this string)
    je .eof
    test al, al             ; if read_char ret eof -> .eof
    jz .eof
    cmp r8, rsi
    je .overflow            ; if len == buf len -> .owerflow
    jmp .char               ; else -> char
.eof:
    cmp r8, rsi             
    je .overflow            ; if len == buf len -> overflow
.ok:    
    mov byte[rdi + r8], NULL_TERMINATOR     ; [addr + len] - position of \0
    mov rdx, r8
    mov rax, rdi
    ret
.overflow:
    mov rax, 0
    ret
     

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
    xor rax, rax
    mov rsi, 10
    xor r8, r8
    xor r9, r9
.loop:    
    mov r9b, byte[rdi + r8]
    cmp r9b, '0'
    jb .end
    cmp r9b, '9'
    ja .end
    mul rsi
    sub r9b, '0'
    add rax, r9
    inc r8
    jmp .loop
.end:
    mov rdx, r8
    ret


; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int:
    xor rax, rax
    xor r9, r9
    mov r9b, byte[rdi]
    cmp r9b, '-'
    jne parse_uint
    inc rdi
    call parse_uint
    test rdx, rdx
    jz .end
    neg rax
    inc rdx
.end:
    ret 

; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
; rdi - str addr, rsi - buf addr, rdx - buf len
string_copy:
    push rdi            ;save caller saved reg
    push rsi
    push rdx
    call string_length
    pop rdx
    pop rsi
    pop rdi
    cmp rax, rdx
    jae .err
    xor r9, r9
    xor r8, r8
.loop:
    mov r9b, byte[rdi + r8]
    mov byte[rsi + r8], r9b 
    cmp byte[rsi + r8], NULL_TERMINATOR
    je .ok
    inc r8
    jmp .loop
.err:
    xor rax, rax  
.ok: 
    ret



; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор
; Отличие от функции read_word в том, что эта функция допускает функции с пробельными символами НЕ В НАЧАЛЕ строки.
; Пример: 
; Строка 'hello world' будет записана функцей read_line без изменений, функция read_word считает только 'hello' 

read_line:              
    xor r8, r8              ; size of word
.start:
	push r8
    push rdi
    push rsi
    call read_char          ; read new char
    pop rsi
    pop rdi
    pop r8
    cmp al, SPACE           ; if char == \s -> .start
    je .start
    cmp al, TAB             ; if char == \s -> .start
    je .start
    cmp al, LINE_FEED
    je .start               ; if char == \s -> .start
    test al, al             ; if read_char ret eof (string = \0) -> .ok
    jz .ok					; else -> .char
.char:
    mov byte[rdi + r8], al  ; move char to buffer
    inc r8                  ; len++
    push r8
    push rdi
    push rsi
    call read_char
    pop rsi
    pop rdi
    pop r8
    test al, al             ; if read_char ret eof -> .eof
    jz .eof
    cmp r8, rsi
    je .overflow            ; if len == buf len -> .owerflow
    jmp .char               ; else -> char
.eof:
    cmp r8, rsi             
    je .overflow            ; if len == buf len -> overflow
.ok:    
    mov byte[rdi + r8], NULL_TERMINATOR     ; [addr + len] - position of \0
    mov rdx, r8
    mov rax, rdi
    ret
.overflow:
    mov rax, 0
    ret

