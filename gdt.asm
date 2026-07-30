;db 1 bayt : uint8_t
;dw 2 bayt : uint16_t
;dd 4 bayt : uint32_t

gdt_nulldesc:
    dd 0    ;4 bayt
    dd 0    ;4 bayt

gdt_codedesc:
    dw 0xffff       ;limit
    dw 0x0000       ;base(low)
    db 0x00         ;base(medium)

    ;accessByte
    ;P(1), DPL(2), S(1),E(1), DC(1), RW(1), A(1)
    
    ;P(1): Konum
    ;DPL(2): Erisim seviyesi
    ;S(1): Tablo tipi
    ;E(1): Calistirilabilirlik
    ;DC(1): Yetki seviyesi
    ;RW(1): Okuma/yazma izni        
    db 10011010b

    ;Flags
    ;G, DB, L, AVL, limit

    ;G(1): Parca boyutu
    ;DB(1): ?
    ;L(1): 64bit mod
    ;Rezerv(1)
    ;Limit(4)
    db 11001111b

    ;base
    db 0x00         ;base(high)

gdt_datadesc:
    dw 0xffff
    dw 0x0000
    db 0x00
    ;accessByte
    ;P(1), DPL(2), S(1), DC(1), RW(1), A(1)
    db 10010010b
    ;Flags
    ;G, DB, L, AVL, limit
    db 11001111b
    ;base
    db 0x00
gdt_end:

gdt_descriptor:
        dw gdt_end - gdt_nulldesc - 1
        dd gdt_nulldesc

codeseg equ gdt_codedesc - gdt_nulldesc
dataseg equ gdt_datadesc - gdt_nulldesc