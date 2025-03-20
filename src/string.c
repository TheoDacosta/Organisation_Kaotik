#include "string.h"

uint16_t len(const char* str)
{
    uint16_t length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

void str_copy(const char* src, char* dest, uint16_t dest_size)
{
    while (*src != '\0' && dest_size > 1) {
        *dest = *src;
        dest++;
        src++;
        dest_size--;
    }
    *dest = '\0';
}

void add_endline(const char* str, char* dest, uint16_t dest_size)
{
    while (*str != '\0' && dest_size > 2) {
        *dest = *str;
        dest++;
        str++;
        dest_size--;
    }
    *dest = '\n';
    dest++;
    *dest = '\0';
}
