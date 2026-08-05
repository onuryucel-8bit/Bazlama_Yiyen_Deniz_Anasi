#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#include "utils.h"
#include "portio.h"

#define TTY_TEXT_MOD_WIDTH 80
#define TTY_TEXT_MOD_HEIGHT 25


/*

https://brokenthorn.com/Resources/OSDev10.html

Bits 0 - 2: Foreground color
Bit 0: Red
Bit 1: Green
Bit 2: Blue
Bit 3: Foreground Intensity
Bits 4 - 6: Background color
Bit 4: Red
Bit 5: Green
Bit 6: Blue
Bit 7: Blinking or background intensity

  7     6      5      4      3     2     1      0
*=====.======.======.======.=====.=====.======.======*
| bA  |  bB  |  bG  |  bR  | fA  | fB  |  fG  |  fR  |
*=====.======.======.======.=====.=====.======.======*

Bit 76543210
    ||||||||
    |||||^^^-fore color
    ||||^----fore color bright bit
    |^^^-----back color
    ^--------back color bright bit OR enables blinking Text

  [blink]       [background] [foreground] [char]
  [yanip sönme] [arka]       [on]         [karakter]
  [1]           [3]         [4]          [8]
*/

typedef enum
{
    VGA_color_Black,
    VGA_color_Blue,	
    VGA_color_Green,	
    VGA_color_Cyan,	
    VGA_color_Red,   
    VGA_color_Magenta,
    VGA_color_Brown,	
    VGA_color_Gray,	
    VGA_color_DarkGray,
    VGA_color_LightBlue,	
    VGA_color_LightGreen,	
    VGA_color_LightCyan,
    VGA_color_LightRed,
    VGA_color_LightMagenta,
    VGA_color_Yellow,
    VGA_color_White,

}VGAColor;



/*
https://cplusplus.com/reference/cstdio/printf/

d   Signed decimal integer	392
X	Unsigned hexadecimal integer (uppercase)	7FA
F	Decimal floating point, uppercase	392.65
c	Character	a
s	String of characters	sample
p	Pointer address	b8000000
*/
void printf(const char* fmt, ...);
void putchar(char ch);

//==========================================================//
//==========================================================//
//==========================================================//

void setbgColor(VGAColor color);
void setfgColor(VGAColor color);

VGAColor getfgColor();
VGAColor getbgColor();



static void print_char(uint8_t ch);
static void print_int(uint32_t value);
static void print_hex(uint32_t value);
static void print_float();
static void print_double();
static void print_string(const char* str);

#endif