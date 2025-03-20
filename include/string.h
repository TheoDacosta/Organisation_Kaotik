#ifndef STRING_H
#define STRING_H

#include <stdint.h>

uint16_t len(const char* str);
void str_copy(const char* src, char* dest, uint16_t dest_size);
void add_endline(const char* str, char* dest, uint16_t dest_size);

#endif // STRING_H
