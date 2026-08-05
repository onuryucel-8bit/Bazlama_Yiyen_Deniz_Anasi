#include "vga.h"

uint16_t get_cursorPosition()
{
    uint16_t pos = 0;

    //cursor low
    outb(VGA_REG_PORT, VGA_REG_Cursor_Location_Low);
    pos |= inb(VGA_DATA_PORT);

    //cursor high
    outb(VGA_REG_PORT, VGA_REG_Cursor_Location_High);
    pos |= ((uint16_t)inb(VGA_DATA_PORT)) << 8;

    return pos;
}

//http://www.osdever.net/FreeVGA/vga/crtcreg.htm
void set_cursor(int x, int y)
{
	uint16_t pos = y * TTY_TEXT_MOD_WIDTH + x;

    //select internal VGA register
	outb(VGA_REG_PORT, VGA_REG_Cursor_Location_Low);
    //read/write selected register
	outb(VGA_DATA_PORT, (uint8_t) (pos & 0xFF));

	outb(VGA_REG_PORT, VGA_REG_Cursor_Location_High);
	outb(VGA_DATA_PORT, (uint8_t) ((pos >> 8) & 0xFF));
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(VGA_REG_PORT, VGA_REG_Cursor_Start);
	outb(VGA_DATA_PORT, (inb(VGA_DATA_PORT) & 0xC0) | cursor_start);

	outb(VGA_REG_PORT, VGA_REG_Cursor_Start);
	outb(VGA_DATA_PORT, (inb(VGA_DATA_PORT) & 0xE0) | cursor_end);
}

void disable_cursor()
{
	outb(VGA_REG_PORT, VGA_REG_Cursor_Start);
	outb(VGA_DATA_PORT, 0x20);
}
