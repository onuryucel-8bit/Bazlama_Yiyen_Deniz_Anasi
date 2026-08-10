#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "portio.h"
#include "stdio.h"
#include "idtKey.h"

#define EOI 0x20 //End of interrupt
#define PORT_KEYBOARD_DATA 0x60 //keyboard data port

#define TOTAL_INTERRUPTS 256

#define PIC_MASTER 0x20
#define PIC_MASTER_DATA 0x21

#define PIC_SLAVE  0xA0
#define PIC_SLAVE_DATA 0xA1

#define ICW1_INIT          0x10
#define ICW4               0x01
#define ICW3_MASTER        0x04
#define ICW3_SLAVE         0x02

#define INIT_COMMAND_WORD  (ICW1_INIT | ICW4)

#define PIC_UNMASK_ALL 0x0

//kesme adres bilgisi ve diger zamazingolar
typedef struct __attribute__((packed))
{
    uint16_t offset_lower;  //adres
    uint16_t selector;      //gdt code segment selector(kernel code segment)  
    uint8_t zero;           //Rezerv her zaman sifir, x86 islemci programcinin erisiminin olmadigi ic kisimda kullaniliyor galiba       
    uint8_t types_attr;     //Present bit | privilege level | gate type
    uint16_t offset_upper;  //adres
} IDT;

//kesme boyutu nerde baslayip bittigi hakkinda bilgi
typedef struct __attribute__((packed))
{
    uint16_t limit;
    uint32_t base;

}idtr;

void idt_init();

uint8_t tolower(uint8_t ch);

void no_interrupt_handler();
void idt_keyboard_handler();

static void idt_set(int intrerrupt_no, void* address);
static void pic_remap();

#endif