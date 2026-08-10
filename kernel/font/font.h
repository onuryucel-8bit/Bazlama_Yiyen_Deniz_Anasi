#ifndef FONT_H
#define FONT_H

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>


extern const uint8_t font8[128][8];

/*
//https://github.com/dhepper/font8x8

Encoding
========
Every character in the font is encoded row-wise in 8 bytes.

The least significant bit of each byte corresponds to the first pixel in a row. 

The character 'A' (0x41 / 65) is encoded as 
{ 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00}


    0x0C => 0000 1100 => ..XX....
    0X1E => 0001 1110 => .XXXX...
    0x33 => 0011 0011 => XX..XX..
    0x33 => 0011 0011 => XX..XX..
    0x3F => 0011 1111 => xxxxxx..
    0x33 => 0011 0011 => XX..XX..
    0x33 => 0011 0011 => XX..XX..
    0x00 => 0000 0000 => ........

To access the nth pixel in a row, right-shift by n.

                         . . X X . . . .
                         | | | | | | | |
    (0x0C >> 0) & 1 == 0-+ | | | | | | |
    (0x0C >> 1) & 1 == 0---+ | | | | | |
    (0x0C >> 2) & 1 == 1-----+ | | | | |
    (0x0C >> 3) & 1 == 1-------+ | | | |
    (0x0C >> 4) & 1 == 0---------+ | | |
    (0x0C >> 5) & 1 == 0-----------+ | |
    (0x0C >> 6) & 1 == 0-------------+ |
    (0x0C >> 7) & 1 == 0---------------+
*/
#endif