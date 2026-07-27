org 0x7c00
bits 16

cli
xor ax, ax  ; ax = 0
mov ds, ax
mov es, ax
mov ss, ax
mov fs, ax
mov gs, ax

mov sp, 0x7b00



mov si, hata_mesaj
call printStr

jmp $

;GIRDI
;si <= str baslangic adresi
printStr:
    .dongu:
        mov al, [si]    ;ram[si] => al
        inc si          ;si++

        cmp al, 0       ;al ?= '\0'
        je .bitis

        call printChar
        jmp .dongu
.bitis
ret


;GIRDI
;al <= ekrana basilacak karakter
printChar:
    mov ah, 0x0e    ;tty mod
    int 0x10
ret

yukleme_mesaj: db "Kernel yukleniyor",0
hata_mesaj: db "Kernel acilmadi:|",0

;0x7c0a - 0x7c00
%assign SIZE ($ - $$)
%warning "Kullanilan alan = " (SIZE) " bayt"

;bos alan
%assign SIZE_empty (510 - SIZE)
%warning "Bos alan = " (SIZE_empty) " bayt"

times 510 - ($ - $$) db 0
dw 0xAA55