#include "stdio.h"

void putchar(char ch)
{
    print_char(ch);
} 

void printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
        
    while (*fmt)
    {
        if(*fmt == '%')
        {
            fmt++;

            switch (*fmt)
            {           
            case 'd':            
                int n = va_arg(args, int);
                print_int(n);
                fmt++;                
                break;
            
            case 'x':
            case 'X':
                int hex = va_arg(args, int);
                print_hex(hex);
                fmt++;
                break;
            
            case 'c':
                char ch = (char)va_arg(args, int);
                print_char(ch);
                fmt++;
                break;

            case 's':
                char* c = va_arg(args, char*);
                print_string(c);
                fmt++;
                break;

            default:
                break;
            }
        
        }
        else
        {
            putchar(*fmt);
            fmt++;            
        }
    }//while end
    

    va_end(args);
}//printf end

//============================================================//
//============================================================//
//============================================================//

//private:
static uint16_t* vga = (uint16_t*)0xb'8000;
static uint16_t vgaIndex = 0;

static VGAColor vgaColor = VGA_color_Green;

//public:


//[renk 4bit][.]
void setbgColor(VGAColor color)
{
    vgaColor = vgaColor | (color << 4);
}

//[.][renk 4bit]
void setfgColor(VGAColor color)
{
    vgaColor = vgaColor | color;
}

VGAColor getfgColor()
{
    return vgaColor & 0x0f;
}

VGAColor getbgColor()
{
    return (vgaColor >> 4) & 0x0f;
}

#pragma region private_print

void print_char(uint8_t ch)
{
    switch (ch)
    {
    case '\n':
    /*
        vgainde = 20
        20 + 80 => 100
        
        100 % 80 = 20
        100 - 20 = 80
    */
        vgaIndex += TTY_TEXT_MOD_WIDTH;        
        vgaIndex = vgaIndex - (vgaIndex % TTY_TEXT_MOD_WIDTH);
        break;
    
    default:
        vga[vgaIndex] = (uint16_t)((vgaColor << 8) | ch);
        vgaIndex++;
        break;
    }
}

void print_int(uint32_t value)
{
    //int => str`    
    //print_str(str`)
    char str[32];
    uti_intToStr(value, str);
    print_string(str);
}

void print_float(){}
void print_double(){}

void print_hex(uint32_t value)
{
    char buffer[9];
    uti_intToHex(value, buffer);
    print_string("0x");
    
    const char* ptr = buffer;
    uint8_t counter = 0;
    while (*ptr)
    {                
        print_char(*ptr);
        ptr++;
        counter++;
        if(counter == 4)
        {
            print_char('\'');
        }
    }
}

void print_string(const char* str)
{
    while(*str)
    {
        print_char(*str);
        str++;
    }
}
#pragma endregion

