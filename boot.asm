org 0x7c00
bits 16

.main:

mov ah, 0x0     ;klavye modu
int 0x16        ;klavye => al(ascii) karakter

mov ah, 0x0e    ;tty mod
int 0x10

jmp .main

jmp $

times 510 - ($ - $$) db 0
dw 0xAA55