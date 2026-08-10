#ifndef IDTKEY_H
#define IDTKEY_H

#include <stdint.h>

extern const uint8_t* scancode_names[256];

typedef enum
{
    IDT_KEY_ESC         = 0x01,

    IDT_KEY_1           = 0x02,
    IDT_KEY_2           = 0x03,
    IDT_KEY_3           = 0x04,
    IDT_KEY_4           = 0x05,
    IDT_KEY_5           = 0x06,
    IDT_KEY_6           = 0x07,
    IDT_KEY_7           = 0x08,
    IDT_KEY_8           = 0x09,
    IDT_KEY_9           = 0x0A,
    IDT_KEY_0           = 0x0B,

    IDT_KEY_MINUS       = 0x0C,
    IDT_KEY_EQUALS      = 0x0D,
    IDT_KEY_BACKSPACE   = 0x0E,
    IDT_KEY_TAB         = 0x0F,

    IDT_KEY_Q           = 0x10,
    IDT_KEY_W           = 0x11,
    IDT_KEY_E           = 0x12,
    IDT_KEY_R           = 0x13,
    IDT_KEY_T           = 0x14,
    IDT_KEY_Y           = 0x15,
    IDT_KEY_U           = 0x16,
    IDT_KEY_I           = 0x17,
    IDT_KEY_O           = 0x18,
    IDT_KEY_P           = 0x19,

    IDT_KEY_LBRACKET    = 0x1A,
    IDT_KEY_RBRACKET    = 0x1B,

    IDT_KEY_ENTER       = 0x1C,
    IDT_KEY_LCTRL       = 0x1D,

    IDT_KEY_A           = 0x1E,
    IDT_KEY_S           = 0x1F,
    IDT_KEY_D           = 0x20,
    IDT_KEY_F           = 0x21,
    IDT_KEY_G           = 0x22,
    IDT_KEY_H           = 0x23,
    IDT_KEY_J           = 0x24,
    IDT_KEY_K           = 0x25,
    IDT_KEY_L           = 0x26,

    IDT_KEY_SEMICOLON   = 0x27,
    IDT_KEY_APOSTROPHE  = 0x28,
    IDT_KEY_GRAVE       = 0x29,

    IDT_KEY_LSHIFT      = 0x2A,
    IDT_KEY_BACKSLASH   = 0x2B,

    IDT_KEY_Z           = 0x2C,
    IDT_KEY_X           = 0x2D,
    IDT_KEY_C           = 0x2E,
    IDT_KEY_V           = 0x2F,
    IDT_KEY_B           = 0x30,
    IDT_KEY_N           = 0x31,
    IDT_KEY_M           = 0x32,

    IDT_KEY_COMMA       = 0x33,
    IDT_KEY_PERIOD      = 0x34,
    IDT_KEY_SLASH       = 0x35,

    IDT_KEY_RSHIFT      = 0x36,
    IDT_KEY_KP_MUL      = 0x37,
    IDT_KEY_LALT        = 0x38,
    IDT_KEY_SPACE       = 0x39,
    IDT_KEY_CAPSLOCK    = 0x3A,

    IDT_KEY_F1          = 0x3B,
    IDT_KEY_F2          = 0x3C,
    IDT_KEY_F3          = 0x3D,
    IDT_KEY_F4          = 0x3E,
    IDT_KEY_F5          = 0x3F,
    IDT_KEY_F6          = 0x40,
    IDT_KEY_F7          = 0x41,
    IDT_KEY_F8          = 0x42,
    IDT_KEY_F9          = 0x43,
    IDT_KEY_F10         = 0x44,

    IDT_KEY_NUMLOCK     = 0x45,
    IDT_KEY_SCROLLLOCK  = 0x46,

    IDT_KEY_KP_7        = 0x47,
    IDT_KEY_KP_8        = 0x48,
    IDT_KEY_KP_9        = 0x49,
    IDT_KEY_KP_MINUS    = 0x4A,
    IDT_KEY_KP_4        = 0x4B,
    IDT_KEY_KP_5        = 0x4C,
    IDT_KEY_KP_6        = 0x4D,
    IDT_KEY_KP_PLUS     = 0x4E,
    IDT_KEY_KP_1        = 0x4F,
    IDT_KEY_KP_2        = 0x50,
    IDT_KEY_KP_3        = 0x51,
    IDT_KEY_KP_0        = 0x52,
    IDT_KEY_KP_PERIOD   = 0x53,

    IDT_KEY_F11         = 0x57,
    IDT_KEY_F12         = 0x58

} IDTKey;

#endif