#include "portio.h"

//https://wiki.osdev.org/Inline_Assembly/Examples
//https://wiki.osdev.org/Port_IO

void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile (
        "outb %0, %1"
        :
        : "a"(value), "Nd"(port)
    );
}

uint8_t inb(uint16_t port)
{
    uint8_t retvalue;

    __asm__ volatile (
        "inb %1, %0"
        : "=a"(retvalue)
        : "Nd"(port)
    );

    return retvalue;
}