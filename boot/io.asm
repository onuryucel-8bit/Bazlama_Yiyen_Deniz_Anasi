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
.bitis:
ret

;GIRDI
;al <= ekrana basilacak karakter
printChar:
    mov ah, 0x0e    ;tty mod
    int 0x10
ret