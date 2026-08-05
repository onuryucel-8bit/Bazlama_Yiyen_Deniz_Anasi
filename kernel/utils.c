#include "utils.h"

//https://www.geeksforgeeks.org/c/how-to-convert-an-integer-to-a-string-in-c/


void uti_intToStr(int N, char* str) 
{
    int i = 0;
  
    // Save the copy of the number for sign
    int sign = N;

    // If the number is negative, make it positive
    if (N < 0)
        N = -N;

    // Extract digits from the number and add them to the
    // string
    while (N > 0) 
    {      
        // Convert integer digit to character and store
      	// it in the str
        str[i++] = N % 10 + '0';
      	N /= 10;
    } 

    // If the number was negative, add a minus sign to the
    // string
    if (sign < 0) 
    {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string to get the correct order
    for (int j = 0, k = i - 1; j < k; j++, k--) 
    {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

void uti_intToHex(uint32_t dec, char* str)
{    
    const char hexChars[] = "0123456789ABCDEF";
    
    for (int i = 7; i >= 0; i--)
    {
        str[i] = hexChars[dec & 0x0F];
        dec >>= 4;
    }

    str[8] = '\0';   
}

//float/double => str

