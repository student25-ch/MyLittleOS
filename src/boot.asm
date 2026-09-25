[bits 32]
global start
extern kmain

start:
    ; 设置栈
    mov esp, 0x90000
    mov ebp, esp
    call kmain
    jmp $
