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
static uint8_t* vga = (uint8_t*)0xA0000;
static uint16_t vgaIndex = 0;
static uint16_t vgax = 0;
static uint16_t vgay = 0;
static VGAColor fgColor = VGA_color_Green;
static VGAColor bgColor = VGA_color_Black;

//public:
void setbgColor(VGAColor color)
{
    bgColor = color;
}

void setfgColor(VGAColor color)
{
    fgColor = color;
}

VGAColor getfgColor()
{
    return fgColor;
}

VGAColor getbgColor()
{
    return bgColor;
}

#pragma region Cizim_fonksiyonlari

void drawPixel(uint16_t x, uint16_t y, VGAColor color)
{
	vga[y * 320 + x] = color;
}

void drawline(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, VGAColor color)
{
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;

   /*
        =========================
        if |deltaX| >= |deltaY|
            sideLength = |deltaX|

        else
            sideLength = |deltaY|
        =========================
        
        veya

        =========================
        sideLength = max( |deltax|, |deltay|)
        =========================
    */
   
    int sideLength = abs(deltaX) >= abs(deltaY) ? abs(deltaX) : abs(deltaY);

    //x,y koordinatlarinda adim sayisini hesapliyoruz
    float incX = deltaX / (float)sideLength;
    float incY = deltaY / (float)sideLength;

    float currentX = x0;
    float currentY = y0;

    for (size_t i = 0; i <= sideLength; i++)
    {
        drawPixel((int)currentX, (int)currentY, color);
        currentX += incX;
        currentY += incY;
    }
}

void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, VGAColor color)
{
    drawline(x0, y0, x1, y1, color);
    drawline(x1, y1, x2, y2, color);
    drawline(x2, y2, x0, y0, color);
}

void drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, VGAColor color)
{
    drawline(x, y, x + width, y, color);
    drawline(x + width, y, x + width, y + height, color);
    drawline(x + width, y + height, x, y + height, color);
    drawline(x, y + height, x, y, color);
}

void drawFilledRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, VGAColor color)
{
    for (size_t posy = y; posy < height + y; posy++)
    {
        for (size_t posx = x; posx < width + x; posx++)
        {
            drawPixel(posx, posy, color);
        }
    }    
}

#pragma endregion


#pragma region private_print

void print_char(uint8_t ch)
{    
    if(vgay >= WINDOW_HEIGHT)
    {
        vgay = 0;
    }

    if(vgax > WINDOW_WIDTH)
    {
        vgax = 0;
    }

    switch (ch)
    {
    case '\n':
        vgay += 8;
        vgax = 0;
        
        return;

    case '\t':
        vgax += 16;
        return;

    default:
        break;
    }
    
    uint16_t start_x = vgax;
    uint16_t start_y = vgay;

    for (uint8_t row = 0; row < 8; row++)
    {
        uint8_t line = font8[ch][row];
        uint8_t mask = 1;

        for (int8_t col = 0; col < 8; col++)
        {
            uint8_t bit = (line & mask) >> col;
            mask <<= 1;

            if(bit == 1)
            {
                drawPixel(start_x, start_y, fgColor);
            }
            else
            {
                drawPixel(start_x, start_y, bgColor);
            }

            start_x++;
        }
        
        start_x = vgax;        
        start_y++;
    }

    vgax += 8;    
        
    if(vgax >= WINDOW_WIDTH)
    {
        vgax = 0;
        vgay += 8;
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

