%include "boot/SektorSayisi.asm"

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

;a20 kapisi ac
call enableA20

;cekirdegi yukle
call diskOku

;VGA 320x200 moduna gec
mov ax, 0x13
int 0x10

;gdt tablosunu yukle
lgdt [gdt_descriptor]

;cr0 bellegini ayarla
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

    mov esp, 0x00f0_0002
    mov ebp, 0x00f0_0000
   
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