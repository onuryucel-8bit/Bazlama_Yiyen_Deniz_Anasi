#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

uint16_t* vga = (uint16_t*)0xb8000;
uint16_t vgaIndex = 0;

typedef enum 
{
    Black,
    Blue,	
    Green,	
    Cyan,	
    Red,   
    Magenta,
    Brown,	
    Gray,	
    DarkGray,
    LightBlue,	
    LightGreen,	
    LightCyan,	
    LightRed,
    LightMagenta,
    Yellow,
    White,

}Color_t;

void print_char(uint8_t ch, Color_t color)
{
    vga[vgaIndex] = (uint16_t)(ch | (color << 8));
    vgaIndex++;
}

void print_string(const char* str, Color_t color)
{
    while(*str)
    {
        print_char(*str, color);
        *str++;
    }
}

void kernel_main()
{
    print_string("Bazlama Yiyen Deniz Anasi", Yellow);

    
    


    while(1)
    {
        __asm__("hlt");
    }
}