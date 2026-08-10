#include "stdio.h"
#include "idt/idt.h"

#define DEBUG_SERIAL_PORT

#ifdef DEBUG_SERIAL_PORT

    #define PORT_COM1 0x3f8          // COM1

    #define DEBUG_init() init_serial()

    #define DEBUG_printChar(ch) write_serial(ch)
    #define DEBUG_printStr(str) write_serialStr(str)

    int init_serial() 
    {
        outb(PORT_COM1 + 1, 0x00);    // Disable all interrupts
        outb(PORT_COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
        outb(PORT_COM1 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
        outb(PORT_COM1 + 1, 0x00);    //                  (hi byte)
        outb(PORT_COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
        outb(PORT_COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
        outb(PORT_COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
        outb(PORT_COM1 + 4, 0x1E);    // Set in loopback mode, test the serial chip
        outb(PORT_COM1 + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

        // Check if serial is faulty (i.e: not same byte as sent)
        if(inb(PORT_COM1 + 0) != 0xAE) 
        {
            return 1;
        }

        // If serial is not faulty set it in normal operation mode
        // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
        outb(PORT_COM1 + 4, 0x0F);

        return 0;
    }
    
    int is_transmit_empty() 
    {
        return inb(PORT_COM1 + 5) & 0x20;
    }

    void write_serial(char a) 
    {
        while (is_transmit_empty() == 0);

        outb(PORT_COM1,a);
    }

    void write_serialStr(const char* str)
    {
        while (*str)
        {
            write_serial(*str++);                        
        }   
    }
#else
    #define DEBUG_init() ((void)0)

    #define DEBUG_printChar(ch) ((void)0)
    #define DEBUG_printStr(str) ((void)0)

#endif

void kernel_main()
{
    DEBUG_init();
    idt_init();
               
    printf("=========================\n");
    printf("Bazlama Yiyen Deniz Anasi\n");
    printf("=========================\n");   
    

    while(1)
    {
        __asm__("hlt");
    }
}

