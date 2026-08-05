#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void uti_intToStr(int N, char* str);

//str[] uzunlugu 9 OLMAK ZORUNDA sonunda '\0' karakteri var
//cikti => "ffff ffff"
void uti_intToHex(uint32_t dec, char* str);

#endif