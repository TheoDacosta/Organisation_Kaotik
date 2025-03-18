#ifndef STRING_H
#define STRING_H

#include <stdint.h>

uint16_t len(const char* str);
void str_copy(const char* src, char* dest);
void add_endline(const char* str, char* dest);

#endif // STRING_H
