#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#include "stdio.h"

#define VGA_REG_PORT   0x3D4
#define VGA_DATA_PORT  0x3D5

//http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0A

#define VGA_REG_Cursor_Location_Low 0x0F
#define VGA_REG_Cursor_Location_High 0x0E
#define VGA_REG_Cursor_Start 0x0A

//https://wiki.osdev.org/Text_Mode_Cursor

uint16_t get_cursorPosition();
void set_cursor(int x, int y);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor();

#endif