%define SEKTOR_ADETI 1

org 0x7c00
bits 16

cli
;butun s belleklerini sifirla
xor ax, ax  ; ax = 0
mov ds, ax
mov es, ax
mov ss, ax
mov fs, ax
mov gs, ax

mov sp, 0x7b00

mov [HDD_indeks], dl

call enableA20

call diskOku

;gdt tablosunu yukle
lgdt [gdt_descriptor]

mov eax, cr0
or eax, 1
mov cr0, eax

jmp codeseg:StartPM

;===============================;

enableA20:
    in al, 0x92
    or al, 0x2
    out 0x92, al
ret

diskOku:
    mov ah, 0x2
    mov al, SEKTOR_ADETI ;okunacak sektor adeti
    mov ch, 0x0 ;disk numarasi
    mov cl, 0x2 ;sektor numarasi
    mov dh, 0x0 ;kafa numarasi
    mov dl, [HDD_indeks] ;hangi hdd?
    mov bx, KabakCekirdegi
    int 0x13
    jc .yuklemeHatasi
ret

.yuklemeHatasi:
    mov si, hata_mesaj
    call printStr
jmp $


%include "boot/gdt.asm"
%include "boot/io.asm"

HDD_indeks: db 0

hata_mesaj: db "Kernel acilmadi:|",0

;=========================================================;
;=========================================================;
;=========================================================;

bits 32
StartPM:
    mov ax, dataseg

    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    ;vga adresi
    mov ebx, 0xb_8000

    mov esp, 0x00f0_0002
    mov ebp, 0x00f0_0000

    ;2000 => 80x25 dongu limiti
    ;herbir hucre 2 bayt

    ;maviBosluk = 0x1000
    ;for(i = 0; i < 2000; i++)
    ;{
    ;   print(maviBosluk);
    ;   imlec += 2 add ebx, 2
    ;}

    ;maviBosluk = 0x1000
    ;0x1000 acilimi:
    ;Renk
    ;    
    ;       |Arka Plan Rengi| On Plan Rengi |
    ;-------|----|----|-----|---|---|---|---|
    ; blink | R  |  G |  B  | A | R | G | B |
    ;-------|----|----|-----|---|---|---|---|
    ;   1   |  1     1    1 | 1   1   1   1 |
    ;---1---|-------3-------|-------4-------|


    ;     |---8bit-|
    ;0x00 [karakter] ' ' bos karakter 
    ;(ascii_tablosu[0x00] => ' ')

    mov ecx, 0 ; i = 0;
    .dongu:        
        ;ekrani maviye boya
        mov word [ebx], 0x1000

        ;iki bayt kaydir
        add ebx, 2      ;imlec += 2
        add ecx, 1      ;i++
        cmp ecx, 2000   ;i ?= 2000
        jne .dongu

    jmp KabakCekirdegi


;0x7c0a - 0x7c00
%assign SIZE ($ - $$)
%warning "Kullanilan alan = " (SIZE) " bayt"

;bos alan
%assign SIZE_empty (510 - SIZE)
%warning "Bos alan = " (SIZE_empty) " bayt"

times 510 - ($ - $$) db 0
dw 0xAA55

;0x7e00 kabak cekirdegi buraya yuklenicek
KabakCekirdegi: