_start:
    movq $1, %RAX
    cmpq $1, %RDI
    jz .exit
.loop:
    testq %RSI, %RSI
    jz .exit
    mulq %RDI
    dec %RSI
    jmp .loop
.exit:
    ret
