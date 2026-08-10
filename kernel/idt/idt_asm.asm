[bits 32]

global idt_load
global no_interrupt
global isr_keyboard

extern no_interrupt_handler
extern idt_keyboard_handler

;https://en.wikibooks.org/wiki/X86_Disassembly/Calling_Conventions
idt_load:
    push ebp
    
    mov ebp, esp    ;stack base pointer(ebp) = stack pointer(esp)
   
    mov ebx, [ebp + 8] ;ebp + 8 => *idtr
    lidt [ebx]  ;kesme tablosunu idt bellegine yukle
    sti ;kesmeleri ac
    

    pop ebp
ret

no_interrupt:
    
    pusha
    call no_interrupt_handler
    popa
    
iretd

isr_keyboard:
    
    pusha
    call idt_keyboard_handler
    popa
    
iretd