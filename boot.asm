org 0x7c00
bits 16

mov ah, 0x0e    ;tty mod
mov al, 'A'
int 0x10


times 510 - ($ - $$) db 0
dw 0xAA55